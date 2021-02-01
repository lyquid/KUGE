#ifndef KUGE_HEADERS_GAME_H_
#define KUGE_HEADERS_GAME_H_

#include "./event_bus.h"
#include "./input_system.h"
#include "./output_system.h"
#include "../sdl2_wrappers/sdl2_wrappers.h"
#include "../include/resources_path.h"

#include <SDL.h>

class Game {
 public:
  Game() { event_bus_.setSystems(input_sys_, output_sys_); }
  ~Game() { clean(); }

  void handleSDLEvents();
  void handleSDLKeyEvents(const SDL_Keycode& key);
  bool init();
  void render();
  void update();
  
  bool quit_ = false;

 private:
  void clean();
  bool initSDL2();
  bool loadResources();
  
  const SDL_Color kFONT_COLOR_{0xFF, 0x00, 0x00, 0xFF};
  const SDL_Point kSCREEN_SIZE_{1024u, 768u};

  ktp::SDL2_Timer clock_{};
  SDL_Event       sdl_event_{};
  ktp::SDL2_Font  font_{};
  ktp::SDL2_Window main_window_{};
  ktp::SDL2_Renderer renderer_{};

  ktp::SDL2_Music music_{};

  ktp::SDL2_Texture texture_jpg_{};
  ktp::SDL2_Texture texture_png_{};
  ktp::SDL2_Texture texture_text_blended_{};
  ktp::SDL2_Texture texture_text_shaded_{};
  ktp::SDL2_Texture texture_text_solid_{};

  kuge::EventBus event_bus_{};

  kuge::InputSystem  input_sys_{event_bus_};
  kuge::OutputSystem output_sys_{event_bus_};
};

#endif // KUGE_HEADERS_GAME_H_