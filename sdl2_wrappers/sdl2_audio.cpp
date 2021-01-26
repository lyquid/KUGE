#include "./sdl2_audio.h"

void ktp::SDL2_Audio::closeMixer() {
  Mix_CloseAudio();
  while (Mix_Init(0)) Mix_Quit();
}

bool ktp::SDL2_Audio::initMixer(int freq, Uint16 format, int channels, int chunk_size) {
  constexpr auto audio_flags = MIX_INIT_OGG | MIX_INIT_MOD;
  const auto initted = Mix_Init(audio_flags);
  if ((initted & audio_flags) != audio_flags) {
    ktp::logSDLError("Mix_Init");
    return false;
  }
  if (Mix_OpenAudio(freq, format, channels, chunk_size) == -1) {
    ktp::logSDLError("Mix_OpenAudio");
    while (Mix_Init(0)) Mix_Quit();
    return false;
  }
  return true;
}
