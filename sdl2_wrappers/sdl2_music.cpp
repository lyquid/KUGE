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
