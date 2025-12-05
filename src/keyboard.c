/*
=========================================================================================================
Author : Quinn Olney

Purpose: keyboard handler, interacts with the terminal and detects keyboard input to display
=========================================================================================================
*/

#include <stdint.h>
#include "terminal.h"
#include "keyboard.h"
#include "speaker.h"
#include "chords.h"

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}


static const char keymap[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',  
    '\t','q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,   
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',               
    0, '\\','z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',                  
        0,   0,   0, ' '                                                           
    // rest default to 0
};

//--LINE BUFFER--

#define INPUT_MAX 128
static char input_buffer[INPUT_MAX];
static uint32_t input_len = 0;

static int streq(const char* a, const char* b)
{
    while (*a && *b) {
        if (*a != *b){
            return 0;
        }
        else {
            a++; 
            b++;
        }
    }
    return *a == *b;
}

static void execute_command(const char* cmd)
{
    if (streq(cmd, "beep")){
        speaker_beep();
    } else if (streq(cmd, "boop")) {
        terminal_writestring("BEEP\n");
    } else if (streq(cmd, "clear")) {
        terminal_initialize();
    } else if (streq(cmd, "about")) {
        terminal_writestring("Babys first OS, an attempt at something AWESOME\n");
    } else if (streq(cmd, "cmaj")) {
        cmaj();
    } else {
        terminal_writestring("UNKNOWN COMMAND TRY AGAIN\n");
    }

}

static void prompt(void)
{
    terminal_writestring(">");
}

void keyboard_handle_irq(void)
{
    uint8_t sc = inb(0x60);

    // Ignore key releases (high bit set)
    if (sc & 0x80) {
        return;
    }

    char c = 0;
    if (sc < sizeof(keymap)) {
        c = keymap[sc];
    }

    if (!c) {
        return; // unsupported/non-printable
    }

    if (c == '\n') {
        terminal_putchar('\n');
        
        if (input_len > 0) {
            input_buffer[input_len] = '\0';

            execute_command(input_buffer);

            input_len= 0;
        }
        prompt();
        return;
    }

    if (c == '\b') {
        if (input_len > 0){
            input_len--;

            terminal_putchar('\b');
        }
        return;
    }

    if (input_len < INPUT_MAX - 1) {
        input_buffer[input_len++] = c;
        terminal_putchar(c);
    }

    
}