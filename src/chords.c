#include "speaker.h"
#include <stdint.h>

void cmaj(void) 
{
    speaker_play_freq(523); //c
    speaker_delay(250000000);                
    speaker_stop();

    speaker_play_freq(659); //e
    speaker_delay(250000000);                
    speaker_stop();

    speaker_play_freq(784); //g
    speaker_delay(250000000);                
    speaker_stop();

}
void dmin(void)
{
    speaker_play_freq(587); //d
    speaker_delay(250000000);                
    speaker_stop();

    speaker_play_freq(698); //f
    speaker_delay(250000000);                
    speaker_stop();

    speaker_play_freq(880); //a
    speaker_delay(250000000);                
    speaker_stop();
}
void emin(void)
{   
    
    speaker_play_freq(659); //e
    speaker_delay(250000000);                
    speaker_stop();

    speaker_play_freq(784); //g
    speaker_delay(250000000);                
    speaker_stop();

    speaker_play_freq(988); //b
    speaker_delay(250000000);                
    speaker_stop();
}
void fmaj(void)
{
    speaker_play_freq(698); //f
    speaker_delay(250000000);                
    speaker_stop();

    speaker_play_freq(880); //a
    speaker_delay(250000000);                
    speaker_stop();   

    speaker_play_freq(1046); //c
    speaker_delay(250000000);                
    speaker_stop();
}
void gmaj(void)
{
    speaker_play_freq(784); //g
    speaker_delay(250000000);                
    speaker_stop();

    speaker_play_freq(988); //b
    speaker_delay(250000000);                
    speaker_stop();

    speaker_play_freq(1175); //d
    speaker_delay(250000000);                
    speaker_stop();
}
void amin(void)
{
    speaker_play_freq(880); //a
    speaker_delay(250000000);                
    speaker_stop();

    speaker_play_freq(1046); //c
    speaker_delay(250000000);                
    speaker_stop();

    speaker_play_freq(1318); //e
    speaker_delay(250000000);                
    speaker_stop();

}
void bdim(void)
{
    speaker_play_freq(494); //b
    speaker_delay(250000000);                
    speaker_stop();

    speaker_play_freq(587); //d
    speaker_delay(250000000);                
    speaker_stop();

    speaker_play_freq(698); //f
    speaker_delay(250000000);                
    speaker_stop();
}