#include "../headers/game.h"

void Game::handleSDLEvents() {
  while (SDL_PollEvent(&sdl_event_)) {
    switch (sdl_event_.type) {
      case SDL_QUIT:
        input_sys_.postEvent(kuge::EventTypes::ExitGame);
        quit_ = true;
        break;
      case SDL_KEYDOWN:
        input_sys_.postEvent(kuge::EventTypes::KeyPressed, SDL_GetKeyName(sdl_event_.key.keysym.sym));
        handleSDLKeyEvents(sdl_event_.key.keysym.sym);
        break;
      default:
        break;
    }
  }
}

void Game::handleSDLKeyEvents(const SDL_Keycode& key) {
  switch (key) {
    case SDLK_ESCAPE:
      input_sys_.postEvent(kuge::EventTypes::ExitGame);
      quit_ = true;
      break;
    case SDLK_SPACE:
      break;
    case SDLK_9:
      if (!ktp::SDL2_Music::isPlayingMusic()) {
        music_.play();
      }
      else {
        if (ktp::SDL2_Music::isMusicPaused()) {
          ktp::SDL2_Music::resumeMusic();
        }
        else {
          ktp::SDL2_Music::pauseMusic();
        }
      }
      break;
    case SDLK_0:
      ktp::SDL2_Music::stopMusic();
      break;
    default:
      break;
  }
}

bool Game::init() {
  if (!initSDL2()) return false;
  
  if (!main_window_.create(kSCREEN_SIZE_)) return false;
  event_bus_.postEvent(kuge::EventTypes::SDL2_MainWindowCreated);

  if (!renderer_.create(main_window_)) return false; 
  event_bus_.postEvent(kuge::EventTypes::SDL2_RenderCreated);

  if (!loadResources()) return false;

  event_bus_.postEvent(kuge::EventTypes::GameInit);
  return true;
}

bool Game::initSDL2() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    ktp::logSDLError("SDL_Init");
    return false;
  }

  if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
  	ktp::logSDLError("IMG_Init");
	  return false;
  }

  if (!ktp::SDL2_Font::initTTF()) return false;

  if (!ktp::SDL2_Audio::initMixer()) return false;

  event_bus_.postEvent(kuge::EventTypes::SDL2_Initialized);
  return true;
}

bool Game::loadResources() {
  // fonts
  if (!font_.loadFont(ktp::getResourcesPath() + "fonts/Future n0t Found.ttf", 72)) {
    return false;
  }
  // textures
  texture_jpg_.setRenderer(renderer_);
  if (!texture_jpg_.loadFromFile(ktp::getResourcesPath() + "images/im_jpg.jpg")) {
    return false;
  }
  texture_png_.setRenderer(renderer_);
  if (!texture_png_.loadFromFile(ktp::getResourcesPath() + "images/im_png.png")) {
    return false;
  } 
  texture_text_blended_.setRenderer(renderer_);
  if (!texture_text_blended_.loadFromTextBlended(font_, "blended", kFONT_COLOR_)) {
    return false;
  }
  if (!font_.loadFont(ktp::getResourcesPath() + "fonts/BERNHC.TTF", 92)) {
    return false;
  }
  texture_text_shaded_.setRenderer(renderer_);
  if (!texture_text_shaded_.loadFromTextShaded(font_, "shaded", kFONT_COLOR_, {50,255,20,255})) {
    return false;
  }
  if (!font_.loadFont(ktp::getResourcesPath() + "fonts/Future n0t Found.ttf", 72)) {
    return false;
  }
  texture_text_solid_.setRenderer(renderer_);
  if (!texture_text_solid_.loadFromTextSolid(font_, "solid", kFONT_COLOR_)) {
    return false;
  }
  // sounds
  if (!music_.loadMusic(ktp::getResourcesPath() + "audio/Hotline.ogg")) return false;

  event_bus_.postEvent(kuge::EventTypes::ResourcesLoaded);
  return true;
}

void Game::render() {
  renderer_.setDrawColor(0x00, 0x00, 0xFF, 0x00);
  renderer_.clear();

  texture_jpg_.render({0, 0});
  texture_png_.render({texture_jpg_.getWidth(), 0});
  texture_text_blended_.render({texture_png_.getWidth() * 2, 0});
  texture_text_shaded_.render({texture_png_.getWidth() * 2, texture_text_blended_.getHeight()});
  texture_text_solid_.render({texture_png_.getWidth() * 2, texture_text_blended_.getHeight() + texture_text_shaded_.getHeight()});

  renderer_.present();
}

void Game::update() {
  const float delta_time = clock_.restart() / 1000.f;
  event_bus_.processEvents();
}

void Game::clean() {
  ktp::SDL2_Audio::closeMixer();
  ktp::SDL2_Font::closeTTF();
  IMG_Quit();
	SDL_Quit();
}
