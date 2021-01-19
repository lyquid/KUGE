#include "../headers/sdl2_wrappers.h"

ktp::SDL2_Texture::SDL2_Texture():
  texture_(nullptr),
  renderer_(nullptr),
  height_(0u),
  width_(0u) {}

void ktp::SDL2_Texture::free() {
  if (texture_ != nullptr) {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    height_ = 0u;
    width_ = 0u;
  }
}

bool ktp::SDL2_Texture::loadFromFile(const std::string& path) {
  ktp::SDL2_Texture::free();
  const auto surface = IMG_Load(path.c_str());
  if (surface == nullptr) {
    ktp::logSDLError("IMG_Load");
    return false;
  } else {
    texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
    if (texture_ == nullptr) {
      ktp::logSDLError("SDL_CreateTextureFromSurface");
      return false;
    } else {
      height_ = surface->h;
      width_ = surface->w;
    }
    SDL_FreeSurface(surface);
  } 
  return true;
}

void ktp::SDL2_Texture::render(const SDL_Point& where) {
  const SDL_Rect dest = {where.x, where.y, width_, height_};
  SDL_RenderCopy(renderer_, texture_, NULL, &dest);
}