#include "./sdl2_sound.h"

void ktp::SDL2_Sound::free() {
  if (sound_ != nullptr) {
    Mix_FreeChunk(sound_);
    sound_ = nullptr;
  }
}

bool ktp::SDL2_Sound::loadSound(const std::string& path) {
  free();
  sound_ = Mix_LoadWAV(path.c_str());
  if (sound_ == nullptr) {
    ktp::logSDLError("Mix_LoadWAV");
    return false;
  }
  return true;
}

int ktp::SDL2_Sound::play(int loops) {
  return Mix_PlayChannel(-1, sound_, loops);
}