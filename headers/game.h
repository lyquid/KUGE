#ifndef KUGE_HEADERS_GAME_H_
#define KUGE_HEADERS_GAME_H_

#include "./event_bus.h"
#include "./input_system.h"
#include "./output_system.h"
#include "./sdl2_wrappers.h"
#include "../include/cleanup.h"
#include "../include/resources_path.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
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

  ktp::SDL2_Timer clock_;
  SDL_Event       sdl_event_;
  ktp::SDL2_Font  font_;
  SDL_Window*     main_window_;
  SDL_Renderer*   renderer_;

  //Mix_Music* music_ = nullptr;
  ktp::SDL2_Music music_;

  ktp::SDL2_Texture texture_jpg_;
  ktp::SDL2_Texture texture_png_;
  ktp::SDL2_Texture texture_text_blended_;
  ktp::SDL2_Texture texture_text_shaded_;
  ktp::SDL2_Texture texture_text_solid_;

  kuge::EventBus   event_bus_;

  kuge::InputSystem  input_sys_;
  kuge::OutputSystem output_sys_;
};

#endif // KUGE_HEADERS_GAME_H_