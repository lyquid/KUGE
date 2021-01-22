#include "./sdl2_music.h"

bool ktp::SDL2_Music::initMixer(int freq, Uint16 format, int channels, int chunk_size) {
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

void ktp::SDL2_Music::closeMixer() {
  Mix_CloseAudio();
  while (Mix_Init(0)) Mix_Quit();
}

void ktp::SDL2_Music::free() {
  if (music_ != nullptr) {
    Mix_FreeMusic(music_);
    music_ = nullptr;
  }
}

bool ktp::SDL2_Music::loadMusic(const std::string& path) {
  free();
  music_ = Mix_LoadMUS(path.c_str());
  if (music_ == nullptr) {
    ktp::logSDLError("Mix_LoadMUS");
    return false;
  }
  return true;
}
