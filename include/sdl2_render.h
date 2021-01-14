#ifndef KTP_SDL2_RENDER_H_
#define KTP_SDL2_RENDER_H_

#include "cleanup.h"
#include "log.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace ktp{

static SDL_Texture* renderText(const std::string& message, TTF_Font* font,
	                      SDL_Color color, SDL_Renderer* renderer) {
  
  SDL_Surface* surface = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surface == nullptr) {
		ktp::logSDLError("TTF_RenderText");
		return nullptr;
	}

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
    ktp::cleanup(surface);
		ktp::logSDLError("SDL_CreateTextureFromSurface");
    return nullptr;
	}
	
  ktp::cleanup(surface);
	return texture;
}

} // namespace ktp

#endif // KTP_SDL2_RENDER_H_