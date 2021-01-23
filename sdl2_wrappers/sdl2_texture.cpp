#include "./sdl2_texture.h"

ktp::SDL2_Texture::SDL2_Texture():
  texture_(nullptr),
  renderer_(nullptr),
  height_(0),
  width_(0) {}

void ktp::SDL2_Texture::free() {
  if (texture_ != nullptr) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    height_ = 0;
    width_ = 0;
  }
}

bool ktp::SDL2_Texture::loadFromFile(const std::string& path) {
  free();
  const auto surface = IMG_Load(path.c_str());
  if (surface == nullptr) {
    ktp::logSDLError("IMG_Load");
    return false;
  } 
  createTextureFromSurface(*surface);
  SDL_FreeSurface(surface);
  return texture_ != nullptr;
}

bool ktp::SDL2_Texture::loadFromTextBlended(const ktp::SDL2_Font& font, const std::string& text, const SDL_Color& color) {
  free();
  const auto surface = TTF_RenderText_Blended(font.getFont(), text.c_str(), color);
  if (surface == nullptr) {
    ktp::logSDLError("TTF_RenderText_Blended");
    return false;
  } 
  createTextureFromSurface(*surface);
  SDL_FreeSurface(surface);
  return texture_ != nullptr;
}

bool ktp::SDL2_Texture::loadFromTextShaded(const ktp::SDL2_Font& font, const std::string& text, const SDL_Color& fg_color, const SDL_Color& bg_color) {
  free();
  const auto surface = TTF_RenderText_Shaded(font.getFont(), text.c_str(), fg_color, bg_color);
  if (surface == nullptr) {
    ktp::logSDLError("TTF_RenderText_Shaded");
    return false;
  } 
  createTextureFromSurface(*surface);
  SDL_FreeSurface(surface);
  return texture_ != nullptr;
}

bool ktp::SDL2_Texture::loadFromTextSolid(const ktp::SDL2_Font& font, const std::string& text, const SDL_Color& color) {
  free();
  const auto surface = TTF_RenderText_Solid(font.getFont(), text.c_str(), color);
  if (surface == nullptr) {
    ktp::logSDLError("TTF_RenderText_Solid");
    return false;
  } 
  createTextureFromSurface(*surface);
  SDL_FreeSurface(surface);
  return texture_ != nullptr;
}

void ktp::SDL2_Texture::render(const SDL_Point& where) {
  const SDL_Rect dest = {where.x, where.y, width_, height_};
  SDL_RenderCopy(renderer_->getRenderer(), texture_, NULL, &dest);
}

void ktp::SDL2_Texture::createTextureFromSurface(SDL_Surface& surface) {
  texture_ = SDL_CreateTextureFromSurface(renderer_->getRenderer(), &surface);
  if (texture_ == nullptr) {
    ktp::logSDLError("SDL_CreateTextureFromSurface");
  } else {
    height_ = surface.h;
    width_ = surface.w;
  }
}
