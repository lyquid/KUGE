#ifndef KTP_SDL2_RENDER_H_
#define KTP_SDL2_RENDER_H_

#include "cleanup.h"
#include "log.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace ktp{

/* 
Slow Slow Slow, but Ultra Nice over another image
Create a 32-bit ARGB surface and render the given text at high quality, using alpha blending to dither 
the font with the given color. This results in a surface with alpha transparency, so you don't have a 
solid colored box around the text. The text is antialiased. This will render slower than Solid, but in 
about the same time as Shaded mode. The resulting surface will blit slower than if you had used Solid or Shaded. 
Use this when you want high quality, and the text isn't changing too fast. */
static SDL_Texture* renderTextBlended(const std::string& message, TTF_Font* font,
	                                                      SDL_Color color, SDL_Renderer* renderer) {
  
  auto surface = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surface == nullptr) {
		logSDLError("TTF_RenderText_Blended");
		return nullptr;
	}

  auto texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
    cleanup(surface);
		logSDLError("SDL_CreateTextureFromSurface");
    return nullptr;
	}
	
  cleanup(surface);
	return texture;
}

/* 
Slow and Nice, but with a Solid Box
Create an 8-bit palettized surface and render the given text at high quality with the given font and colors. 
The 0 pixel value is background, while other pixels have varying degrees of the foreground color from the 
background color. This results in a box of the background color around the text in the foreground color. 
The text is antialiased. This will render slower than Solid, but in about the same time as Blended mode. 
The resulting surface should blit as fast as Solid, once it is made. Use this when you need nice text, and can live with a box. */
inline static SDL_Texture* renderTextShaded(const std::string& message, TTF_Font* font,
	                                                  SDL_Color fg_color, SDL_Color bg_color, SDL_Renderer* renderer) {
  
  auto surface = TTF_RenderText_Shaded(font, message.c_str(), fg_color, bg_color);
	if (surface == nullptr) {
		logSDLError("TTF_RenderText_Shaded");
		return nullptr;
	}

  auto texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
    cleanup(surface);
		logSDLError("SDL_CreateTextureFromSurface");
    return nullptr;
	}
	
  cleanup(surface);
	return texture;
}

/* 
Quick and Dirty
Create an 8-bit palettized surface and render the given text at fast quality with the given font and color. 
The pixel value of 0 is the colorkey, giving a transparent background when blitted. Pixel and colormap 
value 1 is set to the text foreground color. This allows you to change the color without having to render 
the text again. Palette index 0 is of course not drawn when blitted to another surface, since it is the colorkey, 
and thus transparent, though its actual color is 255 minus each of the RGB components of the foreground color. 
This is the fastest rendering speed of all the rendering modes. This results in no box around the text, but the 
text is not as smooth. The resulting surface should blit faster than the Blended one. Use this mode for FPS and 
other fast changing updating text displays. */
inline static SDL_Texture* renderTextSolid(const std::string& message, TTF_Font* font,
	                                                    SDL_Color color, SDL_Renderer* renderer) {
  
  auto surface = TTF_RenderText_Solid(font, message.c_str(), color);
	if (surface == nullptr) {
		logSDLError("TTF_RenderText_Solid");
		return nullptr;
	}

  auto texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
    cleanup(surface);
		logSDLError("SDL_CreateTextureFromSurface");
    return nullptr;
	}
	
  cleanup(surface);
	return texture;
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
static void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y){
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

} // namespace ktp

#endif // KTP_SDL2_RENDER_H_