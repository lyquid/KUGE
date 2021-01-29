#ifndef KTP_SDL2_WRAPPERS_SDL2_MUSIC_H_
#define KTP_SDL2_WRAPPERS_SDL2_MUSIC_H_

#include "./sdl2_log.h"
#include <SDL_mixer.h>
#include <string>

namespace ktp {

class SDL2_Music {
 public:
  ~SDL2_Music() { free(); }
  
  /**
  * Load music file to use. This can load WAVE, MOD, MIDI, OGG, MP3, FLAC, and 
  * any file that you use a command to play with. 
  * If you are using an external command to play the music, you must call Mix_SetMusicCMD 
  * before this, otherwise the internal players will be used. Alternatively, if 
  * you have set an external command up and don't want to use it, you must call
  * Mix_SetMusicCMD(NULL) to use the built-in players again.
  * @param path Path to the music file to use.
  * @return True on success, or false on errors.
  */
  bool loadMusic(const std::string& path);

  /**
  * Play the loaded music loop times through from start to finish. 
  * The previous music will be halted, or if fading out it waits (blocking) for
  * that to finish.
  * @param loops Number of times to play through the music. 0 plays the music zero
  *         times... -1 plays the music forever (or as close as it can get to that).
  * @return True on success, or false on errors.
  */
  bool play(int loops = -1);

  /**
  * Pause the music playback. You may halt paused music.
  * Note: Music can only be paused if it is actively playing.
  */
  static void pauseMusic() { Mix_PauseMusic(); }

  /**
  * Unpause the music. This is safe to use on halted, paused, and already playing
  * music.
  */
  static void resumeMusic() { Mix_ResumeMusic(); }

  /**
  * Halt playback of music. This interrupts music fader effects. 
  * Any callback set by Mix_HookMusicFinished will be called when the music stops.
  */
  static void stopMusic() { Mix_HaltMusic(); }

  /**
  * Tells you if music is actively playing, or not. 
  * Note: Does not check if the channel has been paused.
  * @return False if the music is not playing, or true if it is playing.
  */
  static bool isPlayingMusic() { return Mix_PlayingMusic() != 0; }

  /**
  * Tells you if music is paused, or not. 
  * Note: Does not check if the music was been halted after it was paused, which 
  * may seem a little weird.
  * @return False if music is not paused. True if it is paused.
  */
  static bool isMusicPaused() { return Mix_PausedMusic() != 0; }

 private:

  /**
  * Free the loaded music. If music is playing it will be halted. 
  * If music is fading out, then this function will wait (blocking) until the 
  * fade out is complete.
  */
  void free();
  
  Mix_Music* music_ = nullptr;
 
  // trying to get rid of the raw pointer
  // need a custom deleter
  /* template <auto fn>
  using deleter_from_fn = std::integral_constant<decltype(fn), fn>;

  template <typename T, auto fn>
  using my_unique_ptr = std::unique_ptr<T, deleter_from_fn<fn>>;

  my_unique_ptr<Mix_Music, Mix_FreeMusic> p{Mix_LoadMUS(path)};
  my_unique_ptr<Mix_Music, Mix_FreeMusic> p_music_;
  */
};

} // end namespace ktp

#endif // KTP_SDL2_WRAPPERS_SDL2_MUSIC_H_