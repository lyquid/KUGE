#ifndef KTP_SDL2_WRAPPERS_SDL2_WINDOW_H_
#define KTP_SDL2_WRAPPERS_SDL2_WINDOW_H_

#include "./sdl2_log.h"
#include <SDL.h>

namespace ktp {

class SDL2_Window {
 public:
  SDL2_Window(): window_(nullptr) {}
  ~SDL2_Window() { free(); }

  bool create(const SDL_Point& size);
  const SDL_Point& getSize() const { return size_; }
  SDL_Window* getWindow() const { return window_; }

 private:
  void free();
  SDL_Point size_;
  SDL_Window* window_;
};

} // end namespace ktp

#endif // KTP_SDL2_WRAPPERS_SDL2_WINDOW_H_