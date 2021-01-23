#include "./sdl2_window.h"

bool ktp::SDL2_Window::create(const SDL_Point& size) {
  window_ = SDL_CreateWindow("KUGE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, size.x, size.y, SDL_WINDOW_SHOWN);
  if (window_ == nullptr) {
	  ktp::logSDLError("SDL_CreateWindow");
    return false;
	}
  SDL_GetWindowSize(window_, &size_.x, &size_.y);
  return true;
}

void ktp::SDL2_Window::free() {
  SDL_DestroyWindow(window_);
  window_ = nullptr;
  size_ = {};
}