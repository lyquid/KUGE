#ifndef KTP_SDL2_WRAPPERS_SDL2_RENDERER_H_
#define KTP_SDL2_WRAPPERS_SDL2_RENDERER_H_

#include "./sdl2_log.h"
#include "./sdl2_window.h"
#include <SDL.h>

namespace ktp {

class SDL2_Renderer {
 public:
  SDL2_Renderer(): renderer_(nullptr) {}
  ~SDL2_Renderer() { free(); }

  bool clear();
  bool create(const SDL2_Window& window);
  SDL_Renderer* getRenderer() const { return renderer_; }
  void present() { SDL_RenderPresent(renderer_); }
  bool setDrawColor(const SDL_Color& color);
  bool setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

 private:
  void free();
  SDL_Renderer* renderer_;
};

} // end namespace ktp

#endif // KTP_SDL2_WRAPPERS_SDL2_RENDERER_H_