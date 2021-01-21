#ifndef KTP_SDL2_WRAPPERS_H_
#define KTP_SDL2_WRAPPERS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

namespace ktp {

/* Original loggers idea from Will Usher */
/* Check it here: https://github.com/Twinklebear/TwinklebearDev-Lessons */

/**
* Log a message to the standard output stream.
* @param msg The message to write, format will be msg + '\n'.
*/
static void logMessage(const std::string& msg) {
  std::cout << msg << '\n';
}

/**
* Log a message to the output stream of our choice.
* @param os The output stream to write the message to.
* @param msg The message to write, format will be msg + '\n'.
*/
static void logMessage(std::ostream& os, const std::string& msg) {
  os << msg << '\n';
}

/**
* Log an SDL error with some error message to the standard output stream.
* @param msg The error message to write, format will be msg error: SDL_GetError() + '\n'.
*/
static void logSDLError(const std::string& msg){
	std::cerr << msg << " error: " << SDL_GetError() << '\n';
}

/**
* Log an SDL error with some error message to the output stream of our choice.
* @param os The output stream to write the message to.
* @param msg The error message to write, format will be msg error: SDL_GetError() + '\n'.
*/
static void logSDLError(std::ostream& os, const std::string& msg){
	os << msg << " error: " << SDL_GetError() << '\n';
}

class SDL2_Font {
 public:
  SDL2_Font();
  ~SDL2_Font() { free(); }
  TTF_Font* getFont() const { return font_; }
  bool loadFont(const std::string& path, int size);

 private:
  void free();
  TTF_Font* font_;
};

class SDL2_Music {
 public:
  SDL2_Music();
  ~SDL2_Music() { free(); }
  bool loadMusic(const std::string& path);
  void play(int loops = -1);

  // static bool mixIsPlayingMusic();

 private:
  void free();
  Mix_Music* music_;
};

class SDL2_Texture {
 public:
  SDL2_Texture();
  ~SDL2_Texture() { free(); }

  int getHeight() const { return height_; }
  int getWidth() const { return width_; }
  SDL_Point getSize() const { return {width_, height_}; }
  bool loadFromFile(const std::string& path);

  /* 
  Slow Slow Slow, but Ultra Nice over another image
  Create a 32-bit ARGB surface and render the given text at high quality, using alpha blending to dither 
  the font with the given color. This results in a surface with alpha transparency, so you don't have a 
  solid colored box around the text. The text is antialiased. This will render slower than Solid, but in 
  about the same time as Shaded mode. The resulting surface will blit slower than if you had used Solid or Shaded. 
  Use this when you want high quality, and the text isn't changing too fast. */
  bool loadFromTextBlended(const SDL2_Font& font, const std::string& text, const SDL_Color& color);

  /* 
  Slow and Nice, but with a Solid Box
  Create an 8-bit palettized surface and render the given text at high quality with the given font and colors. 
  The 0 pixel value is background, while other pixels have varying degrees of the foreground color from the 
  background color. This results in a box of the background color around the text in the foreground color. 
  The text is antialiased. This will render slower than Solid, but in about the same time as Blended mode. 
  The resulting surface should blit as fast as Solid, once it is made. Use this when you need nice text, and can live with a box. */
  bool loadFromTextShaded(const SDL2_Font& font, const std::string& text, const SDL_Color& fg_color, const SDL_Color& bg_color);

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
  bool loadFromTextSolid(const SDL2_Font& font, const std::string& text, const SDL_Color& color);

  void render(const SDL_Point& where);
  void setRenderer(SDL_Renderer* ren) { renderer_ = ren; }

 private:
  void createTextureFromSurface(SDL_Surface& surface);
  void free();

  SDL_Texture* texture_;
  SDL_Renderer* renderer_;
  int height_;
  int width_;
}; // end class SDL2_Texture


class SDL2_Timer {
 public:
  SDL2_Timer();

  bool isPaused() { return started_ && paused_; }
  bool isStarted() { return started_; }
  Uint32 getTicks();
  void pause();
  void resume();
  float restart();
  void start();
  void stop();

 private: 
  Uint32 paused_ticks_;
  Uint32 start_ticks_;
  bool paused_;
  bool started_;
}; // end class SDK2_Timer

} // end namespace ktp

#endif // KTP_SDL2_WRAPPERS_H_