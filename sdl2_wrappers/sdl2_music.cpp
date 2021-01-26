#include "./sdl2_music.h"

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

bool ktp::SDL2_Music::play(int loops) {
  if (Mix_PlayMusic(music_, loops) != 0) {
    ktp::logSDLError("Mix_PlayMusic");
    return false;
  }
  return true;
}
