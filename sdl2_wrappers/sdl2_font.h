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

  /**
  * Load file for use as a font, at ptsize size. This is actually 
  * TTF_OpenFontIndex(file, ptsize, 0). This can load TTF and FON files.
  * @param path Path to the font file to use.
  * @param size Point size (based on 72DPI) to load font as. This basically 
  *             translates to pixel height.
  * @return True on success, or false on errors.
  */
  bool loadFont(const std::string& path, int size);

 private:

  /**
  * Free the memory used by font_, and free font itself as well. 
  * Do not use font_ after this without loading a new font to it.
  */
  void free();

  TTF_Font* font_;
};

} // end namespace ktp

#endif // KTP_SDL2_WRAPPERS_SDL2_FONT_H_