#include <stdint.h>
#include "speaker.h"
#include "terminal.h"


static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

#define PIT_FREQUENCY 1193180
#define PIT_CHANNEL2 0x42
#define PIT_COMMAND 0x43


void speaker_delay(volatile uint32_t count)
{
    while (count--) {
        __asm__ volatile("nop");
    }
}


void speaker_play_freq(uint32_t freq)
{
    if (freq == 0) return;

    uint16_t divisor = (uint16_t)(PIT_FREQUENCY / freq);

    outb(PIT_COMMAND, 0xB6);
    outb(PIT_CHANNEL2, (uint8_t)(divisor & 0xFF));
    outb(PIT_CHANNEL2, (uint8_t)((divisor >> 8) & 0xFF));

    uint8_t tmp = inb(0x61);

    if ((tmp & 0x03) != 0x03){
        outb(0x61, tmp | 0x03);
    }
}


void speaker_stop(void)
{
    uint8_t tmp = inb(0x61) & 0xFC;
    outb(0x61, tmp);
}

void speaker_beep(void)
{
    // example: short A4 beep
    speaker_play_freq(440);
    speaker_delay(50000000);
    speaker_stop();
}
/*

    speaker_play_freq(440); //a        
    delay(50000000);                
    speaker_stop();

    speaker_play_freq(494); //b
    delay(50000000);                
    speaker_stop();

    speaker_play_freq(523); //c
    delay(50000000);                
    speaker_stop();

    speaker_play_freq(587); //d
    delay(50000000);                
    speaker_stop();

    speaker_play_freq(659); //e
    delay(50000000);                
    speaker_stop();

    speaker_play_freq(698); //f
    delay(50000000);                
    speaker_stop();

    speaker_play_freq(784); //g
    delay(50000000);                
    speaker_stop();

    speaker_play_freq(880); //a
    delay(50000000);                
    speaker_stop();
    */
