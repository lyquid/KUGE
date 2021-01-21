#ifndef KTP_SDL2_WRAPPERS_SDL2_MUSIC_H_
#define KTP_SDL2_WRAPPERS_SDL2_MUSIC_H_

#include "./sdl2_log.h"
#include <SDL_mixer.h>

namespace ktp {

class SDL2_Music {
 public:
  SDL2_Music(): music_(nullptr) {}
  ~SDL2_Music() { free(); }
  bool loadMusic(const std::string& path);
  void play(int loops = -1) { Mix_PlayMusic(music_, loops); }

  // static bool mixIsPlayingMusic();

 private:
  void free();
  Mix_Music* music_;
};

} // end namespace ktp

#endif // KTP_SDL2_WRAPPERS_SDL2_MUSIC_H_