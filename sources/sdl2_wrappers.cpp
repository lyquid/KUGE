#include "../headers/sdl2_wrappers.h"

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
  ktp::SDL2_Texture::free();
  const auto surface = IMG_Load(path.c_str());
  if (surface == nullptr) {
    ktp::logSDLError("IMG_Load");
    return false;
  } 
  createTextureFromSurface(*surface);
  SDL_FreeSurface(surface);
  return texture_ != nullptr;
}

bool ktp::SDL2_Texture::loadFromTextBlended(TTF_Font& font, const std::string& text, const SDL_Color& color) {
  ktp::SDL2_Texture::free();
  const auto surface = TTF_RenderText_Blended(&font, text.c_str(), color);
  if (surface == nullptr) {
    ktp::logSDLError("TTF_RenderText_Blended");
    return false;
  } 
  createTextureFromSurface(*surface);
  SDL_FreeSurface(surface);
  return texture_ != nullptr;
}

bool ktp::SDL2_Texture::loadFromTextShaded(TTF_Font& font, const std::string& text, const SDL_Color& fg_color, const SDL_Color& bg_color) {
  ktp::SDL2_Texture::free();
  const auto surface = TTF_RenderText_Shaded(&font, text.c_str(), fg_color, bg_color);
  if (surface == nullptr) {
    ktp::logSDLError("TTF_RenderText_Shaded");
    return false;
  } 
  createTextureFromSurface(*surface);
  SDL_FreeSurface(surface);
  return texture_ != nullptr;
}

bool ktp::SDL2_Texture::loadFromTextSolid(TTF_Font& font, const std::string& text, const SDL_Color& color) {
  ktp::SDL2_Texture::free();
  const auto surface = TTF_RenderText_Solid(&font, text.c_str(), color);
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
  SDL_RenderCopy(renderer_, texture_, NULL, &dest);
}

/* PRIVATE METHODS */

void ktp::SDL2_Texture::createTextureFromSurface(SDL_Surface& surface) {
  texture_ = SDL_CreateTextureFromSurface(renderer_, &surface);
  if (texture_ == nullptr) {
    ktp::logSDLError("SDL_CreateTextureFromSurface");
  } else {
    height_ = surface.h;
    width_ = surface.w;
  }
}
