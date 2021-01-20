#ifndef KTP_SDL2_WRAPPERS_H_
#define KTP_SDL2_WRAPPERS_H_

#include "../include/log.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

namespace ktp {

class SDL2_Texture {
 public:
  SDL2_Texture();
  ~SDL2_Texture() { free(); }

  void free();
  int getHeight() const { return height_; }
  int getWidth() const { return width_; }
  SDL_Point getSize() const { return {width_, height_}; }
  bool loadFromFile(const std::string& path);
  bool loadFromTextBlended(TTF_Font& font, const std::string& text, const SDL_Color& color);
  bool loadFromTextShaded(TTF_Font& font, const std::string& text, const SDL_Color& fg_color, const SDL_Color& bg_color);
  bool loadFromTextSolid(TTF_Font& font, const std::string& text, const SDL_Color& color);
  void render(const SDL_Point& where);
  void setRenderer(SDL_Renderer* ren) { renderer_ = ren; }

 private:
  void createTextureFromSurface(SDL_Surface& surface);

  SDL_Texture* texture_;
  SDL_Renderer* renderer_;
  int height_;
  int width_;
};

} // end namespace ktp

#endif // KTP_SDL2_WRAPPERS_H_