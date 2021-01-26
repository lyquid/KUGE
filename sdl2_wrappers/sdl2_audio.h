#ifndef KTP_SDL2_WRAPPERS_SDL2_AUDIO_H_
#define KTP_SDL2_WRAPPERS_SDL2_AUDIO_H_

#include "./sdl2_log.h"
#include <SDL_mixer.h>

namespace ktp {

namespace SDL2_Audio {

  void closeMixer();
  bool initMixer(int freq      = MIX_DEFAULT_FREQUENCY,
                Uint16 format  = MIX_DEFAULT_FORMAT,
                int channels   = 2, 
                int chunk_size = 1024);
                
} // end namespace SDL2_Audio

} // end namespace ktp

#endif // KTP_SDL2_WRAPPERS_SDL2_AUDIO_H_