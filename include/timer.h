#ifndef KUGE_INCLUDE_TIMER_H_
#define KUGE_INCLUDE_TIMER_H_

#include <SDL.h>

namespace ktp{

class Timer {
 public:
  Timer():
    paused_ticks_(0u),
    start_ticks_(0u),
    paused_(false),
    started_(false) {}

 public:
  bool isPaused() { return started_ && paused_; }
  bool isStarted() { return started_; }
   
  Uint32 getTicks() {
  Uint32 time = 0u;
    if (started_) {
      if (paused_) {
        time = paused_ticks_;
      } else {
        time = SDL_GetTicks() - start_ticks_;
      }
    }
    return time;
  }

  void pause() {
    if (started_ && !paused_) {
      paused_ = true;
      paused_ticks_ = SDL_GetTicks() - start_ticks_;
      start_ticks_ = 0u;
    }
  }

  void resume() { unpause(); }

  float restart() {
    auto time = getTicks();
    stop();
    start();
    return static_cast<float>(time);
  }

  void start() {
    started_ = true;
    paused_ = false;
    start_ticks_ = SDL_GetTicks();
    paused_ticks_ = 0u;
  }

  void stop() {
    started_ = false;
    paused_ = false;
    start_ticks_ = 0u;
    paused_ticks_ = 0u;
  }

  void unpause() {
    if (started_ && paused_) {
      paused_ = false;
      start_ticks_ = SDL_GetTicks() - paused_ticks_;
      paused_ticks_ = 0u;
    }
  }
  
 private: 
  Uint32 paused_ticks_;
  Uint32 start_ticks_;
  bool paused_;
  bool started_;
};

} // namespace ktp

#endif // KUGE_INCLUDE_TIMER_H_