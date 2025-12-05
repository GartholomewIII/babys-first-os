#pragma once 
#include <stdint.h>

void speaker_delay(volatile uint32_t count);


void speaker_play_freq(uint32_t freq);
void speaker_stop(void);


void speaker_beep(void);