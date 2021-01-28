#ifndef KTP_SDL2_WRAPPERS_SDL2_SOUND_H_
#define KTP_SDL2_WRAPPERS_SDL2_SOUND_H_

#include "./sdl2_log.h"
#include <SDL_mixer.h>

namespace ktp {

class SDL2_Sound {
 public:
  ~SDL2_Sound() { free(); }
  
  bool loadSound(const std::string& path);
  int play(int loops = 0);

 private:
  void free();
  Mix_Chunk* sound_ = nullptr;
};

} // end namespace ktp

#endif // KTP_SDL2_WRAPPERS_SDL2_SOUND_H_