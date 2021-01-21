#include "./sdl2_font.h"

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
