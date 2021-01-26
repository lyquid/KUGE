#ifndef KTP_SDL2_WRAPPERS_SDL2_WINDOW_H_
#define KTP_SDL2_WRAPPERS_SDL2_WINDOW_H_

#include "./sdl2_log.h"
#include <SDL.h>

namespace ktp {

class SDL2_Window {
 public:
  SDL2_Window(): window_(nullptr) {}
  ~SDL2_Window() { free(); }

  /**
  * Creates a SDL_Window with the specified size.
  * @param size An SDL_Point structure with the desired size of the window.
  * @return True on success, or false on errors.
  */
  bool create(const SDL_Point& size);

  const SDL_Point& getSize() const { return size_; }
  SDL_Window* getWindow() const { return window_; }

 private:

  /**
  * Destroys the SDL_Window* member, freeing the memory used.
  */
  void free();

  SDL_Point size_;
  SDL_Window* window_;
};

} // end namespace ktp

#endif // KTP_SDL2_WRAPPERS_SDL2_WINDOW_H_