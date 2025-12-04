#include <stdint.h>
#include "terminal.h"
#include "keyboard.h"

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
        return;
    }

    if (c == '\b') {

        terminal_putchar('\b');
        return;
    }

    // Normal printable character
    terminal_putchar(c);
}