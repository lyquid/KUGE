#include "./sdl2_renderer.h"

bool ktp::SDL2_Renderer::clear() {
  if (SDL_RenderClear(renderer_) == 0) return true;
  return false;
}

bool ktp::SDL2_Renderer::create(const SDL2_Window& window) {
  renderer_ = SDL_CreateRenderer(window.getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer_ == nullptr) {
    ktp::logSDLError("SDL_CreateRenderer");
    return false;
  }
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_RenderSetLogicalSize(renderer_, window.getSize().x, window.getSize().y);
  return true;
}

void ktp::SDL2_Renderer::free() {
  SDL_DestroyRenderer(renderer_);
  renderer_ = nullptr;
}

bool ktp::SDL2_Renderer::setDrawColor(const SDL_Color& color) {
  if (setDrawColor(color.r, color.g, color.b, color.a)) return true;
  return false;
}

bool ktp::SDL2_Renderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  if (SDL_SetRenderDrawColor(renderer_, r, g, b, a) == 0) return true;
  return false;
}