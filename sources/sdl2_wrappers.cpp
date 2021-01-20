#include "../headers/sdl2_wrappers.h"

/* class SDL2_Font */

ktp::SDL2_Font::SDL2_Font():
  font_(nullptr) {}

void ktp::SDL2_Font::free() {
  if (font_ != nullptr && TTF_WasInit()) {
    TTF_CloseFont(font_);
    font_ = nullptr;
  }
}

bool ktp::SDL2_Font::loadFont(const std::string& path, int size) {
  free();
  font_ = TTF_OpenFont(path.c_str(), size);
  if (font_ == nullptr) {
    ktp::logSDLError("TTF_OpenFont");
  }
  return font_ != nullptr;
}

/* end class SDL2_Font */


/* class SDL2_Texture */

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
  SDL_RenderCopy(renderer_, texture_, NULL, &dest);
}

/* SDL2_Texture PRIVATE METHODS */

void ktp::SDL2_Texture::createTextureFromSurface(SDL_Surface& surface) {
  texture_ = SDL_CreateTextureFromSurface(renderer_, &surface);
  if (texture_ == nullptr) {
    ktp::logSDLError("SDL_CreateTextureFromSurface");
  } else {
    height_ = surface.h;
    width_ = surface.w;
  }
}

/* end class SDL2_Texture */


/* class SDL2_Timer */

ktp::SDL2_Timer::SDL2_Timer():
  paused_ticks_(0u),
  start_ticks_(0u),
  paused_(false),
  started_(false) {}

Uint32 ktp::SDL2_Timer::getTicks() {
  Uint32 time = 0;
  if (started_) {
    if (paused_) {
      time = paused_ticks_;
    } else {
      time = SDL_GetTicks() - start_ticks_;
    }
  }
  return time;
}

void ktp::SDL2_Timer::pause() {
  if (started_ && !paused_) {
    paused_ = true;
    paused_ticks_ = SDL_GetTicks() - start_ticks_;
    start_ticks_ = 0u;
  }
}

void ktp::SDL2_Timer::resume() {
  if (started_ && paused_) {
    paused_ = false;
    start_ticks_ = SDL_GetTicks() - paused_ticks_;
    paused_ticks_ = 0u;
  }
}

float ktp::SDL2_Timer::restart() {
  auto time = getTicks();
  stop();
  start();
  return static_cast<float>(time);
}

void ktp::SDL2_Timer::start() {
  started_ = true;
  paused_ = false;
  start_ticks_ = SDL_GetTicks();
  paused_ticks_ = 0u;
}

void ktp::SDL2_Timer::stop() {
  started_ = false;
  paused_ = false;
  start_ticks_ = 0u;
  paused_ticks_ = 0u;
}

/* end class SDL2_Timer */