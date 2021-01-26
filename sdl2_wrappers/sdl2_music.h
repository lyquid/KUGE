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
  bool play(int loops = -1);

  static void pauseMusic() { Mix_PauseMusic(); }
  static void resumeMusic() { Mix_ResumeMusic(); }
  static void stopMusic() { Mix_HaltMusic(); }

  static bool isPlayingMusic() { return Mix_PlayingMusic() != 0; }
  static bool isMusicPaused() { return Mix_PausedMusic() != 0; }

 private:
  void free();
  Mix_Music* music_;
};

} // end namespace ktp

#endif // KTP_SDL2_WRAPPERS_SDL2_MUSIC_H_