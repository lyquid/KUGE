#ifndef KUGE_HEADERS_GAME_H_
#define KUGE_HEADERS_GAME_H_

#include "./event_bus.h"
#include "./input_system.h"
#include "./output_system.h"
#include "./sdl2_wrappers.h"
#include "../include/cleanup.h"
#include "../include/log.h"
#include "../include/resources_path.h"
#include "../include/sdl2_render.h"
#include "../include/timer.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Game {
 public:
  Game();
  ~Game() { clean(); }

  void handleSDLEvents();
  void handleSDLKeyEvents(const SDL_Keycode& key);
  bool init();
  void render();
  void update();
  
  bool quit_;

 private:
  void clean();
  
  const SDL_Color kFONT_COLOR_;
  const SDL_Point kSCREEN_SIZE_;

  ktp::Timer    clock_;
  SDL_Event     sdl_event_;
  TTF_Font*     font_;
  SDL_Window*   main_window_;
  SDL_Renderer* renderer_;

  ktp::SDL2_Texture texture_jpg_;
  ktp::SDL2_Texture texture_png_;

  kuge::EventBus   event_bus_;

  kuge::InputSystem  input_sys_;
  kuge::OutputSystem output_sys_;
};

#endif // KUGE_HEADERS_GAME_H_