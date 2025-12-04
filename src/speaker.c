#include <stdint.h>
#include "speaker.h"

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

static void delay(volatile uint32_t count)
{
    while (count--) {
        __asm__ volatile("nop");
    }
}

static void speaker_play_freq(uint32_t freq)
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

static void speaker_stop(void)
{
    uint8_t tmp = inb(0x61) & 0xFC;
    outb(0x61, tmp);
}

void speaker_beep(void)
{
    speaker_play_freq(1000);

    delay(1000000);

    speaker_stop();
}