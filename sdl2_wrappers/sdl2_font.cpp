#include "./sdl2_font.h"

void ktp::SDL2_Font::free() {
  if (font_ != nullptr && TTF_WasInit()) {
    TTF_CloseFont(font_);
    font_ = nullptr;
  }
}

bool ktp::SDL2_Font::initTTF() {
  if (!TTF_WasInit() && TTF_Init() != 0) {
    ktp::logSDLError("TTF_Init");
    return false;
  } else {
    ktp::SDL2_Font::queryTTFVersions();
    ktp::logMessage("TTF_Font compiled version: " +  
                    std::to_string(ktp::SDL2_Font::ttf_compiled_version_.major) + '.' + 
                    std::to_string(ktp::SDL2_Font::ttf_compiled_version_.minor) + '.' + 
                    std::to_string(ktp::SDL2_Font::ttf_compiled_version_.patch));
    ktp::logMessage("TTF_Font linked version: " + 
                    std::to_string(ktp::SDL2_Font::ttf_linked_version_->major) + '.' + 
                    std::to_string(ktp::SDL2_Font::ttf_linked_version_->minor) + '.' + 
                    std::to_string(ktp::SDL2_Font::ttf_linked_version_->patch));
  }
  return true;
}

bool ktp::SDL2_Font::loadFont(const std::string& path, int size) {
  free();
  font_ = TTF_OpenFont(path.c_str(), size);
  if (font_ == nullptr) {
    ktp::logSDLError("TTF_OpenFont");
    return false;
  }
  queryFontInfo();
  return true;
}

void ktp::SDL2_Font::setHinting(int hinting) {
  if (hinting_ != hinting) {
    TTF_SetFontHinting(font_, hinting);
    queryFontInfo();
  }
}

void ktp::SDL2_Font::setKerning(bool allowed) {
  if (kerning_ != allowed) {
    allowed ? TTF_SetFontKerning(font_, 1) : TTF_SetFontKerning(font_, 0);
    queryFontInfo();
  }
}

void ktp::SDL2_Font::setOutline(int outline) {
  if (outline_ != outline) {
    TTF_SetFontOutline(font_, outline);
    queryFontInfo();
  }
}

void ktp::SDL2_Font::setStyle(int style) {
  if (style_ != style) {
    TTF_SetFontStyle(font_, style);
    queryFontInfo();
  }
}

void ktp::SDL2_Font::queryFontInfo() {
  face_family_name_ = TTF_FontFaceFamilyName(font_);
  face_style_name_  = TTF_FontFaceStyleName(font_);
  hinting_          = TTF_GetFontHinting(font_);
  kerning_          = TTF_GetFontKerning(font_) != 0;
  line_skip_        = TTF_FontLineSkip(font_);
  max_ascent_       = TTF_FontAscent(font_);
  max_descent_      = TTF_FontDescent(font_);
  max_height_       = TTF_FontHeight(font_);
  monospaced_       = TTF_FontFaceIsFixedWidth(font_) != 0;
  outline_          = TTF_GetFontOutline(font_);
  style_            = TTF_GetFontStyle(font_);
}

void ktp::SDL2_Font::queryTTFVersions() {
  SDL_TTF_VERSION(&ttf_compiled_version_);
  ttf_linked_version_ = TTF_Linked_Version();
}
