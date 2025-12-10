#include <stdint.h>

#include "audio_assets.h"

#include "../assets/find_your_luv_V1.h"


const uint8_t* const g_audio_files[] = {
    find_your_luv_V1_wav,
};

const uint32_t g_audio_file_sizes[] = {
    find_your_luv_V1_wav_len,
};

const char* const g_audio_file_names[] = {
    "find_your_luv_V1.wav",
};

const uint32_t g_audio_file_count = 1;