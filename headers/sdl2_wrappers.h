#ifndef KTP_SDL2_WRAPPERS_H_
#define KTP_SDL2_WRAPPERS_H_

#include "../include/log.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>

namespace ktp {

class SDL2_Texture {
 public:
  SDL2_Texture();
  ~SDL2_Texture() { free(); }

  void free();
  unsigned int getHeight() const { return height_; }
  unsigned int getWidth() const { return width_; }
  SDL_Point getSize() const { return {width_, height_}; }
  bool loadFromFile(const std::string& path);
  void render(const SDL_Point& where);
  void setRenderer(SDL_Renderer* ren) { renderer_ = ren; }

 private:
  SDL_Texture* texture_;
  SDL_Renderer* renderer_;
  int height_;
  int width_;
};

} // end namespace ktp

#endif // KTP_SDL2_WRAPPERS_H_