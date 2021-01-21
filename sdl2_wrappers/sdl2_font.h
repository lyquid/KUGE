#ifndef KTP_SDL2_WRAPPERS_SDL2_FONT_H_
#define KTP_SDL2_WRAPPERS_SDL2_FONT_H_

#include "./sdl2_log.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace ktp {

class SDL2_Font {
 public:
  SDL2_Font(): font_(nullptr) {}
  ~SDL2_Font() { free(); }
  TTF_Font* getFont() const { return font_; }
  bool loadFont(const std::string& path, int size);

 private:
  void free();
  TTF_Font* font_;
};

} // end namespace ktp

#endif // KTP_SDL2_WRAPPERS_SDL2_FONT_H_