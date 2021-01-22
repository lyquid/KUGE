#include "../headers/game.h"

Game::Game():
  quit_(false),
  kFONT_COLOR_({0xFF, 0x00, 0x00, 0xFF}),
  kSCREEN_SIZE_({1024u, 768u}),
  main_window_(nullptr),
  renderer_(nullptr),
  input_sys_(event_bus_),
  output_sys_(event_bus_) { 
    event_bus_.setSystems(input_sys_, output_sys_);
  }

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
      //If there is no music playing
      if (!ktp::SDL2_Music::isPlayingMusic()) {
        //Play the music
        music_.play();
      }
      //If music is being played
      else {
        //If the music is paused
        if (ktp::SDL2_Music::isMusicPaused()) {
          //Resume the music
          ktp::SDL2_Music::resumeMusic();
        }
        //If the music is playing
        else {
          //Pause the music
          ktp::SDL2_Music::pauseMusic();
        }
      }
      break;
      case SDLK_0:
        //Stop the music
        ktp::SDL2_Music::stopMusic();
      break;
    default:
      break;
  }
}

bool Game::init() {

  if (!initSDL2()) return false;
  
  main_window_ = SDL_CreateWindow("KUGE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kSCREEN_SIZE_.x, kSCREEN_SIZE_.y, SDL_WINDOW_SHOWN);
  // main_window_ = SDL_CreateWindow("KUGE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
  if (main_window_ == nullptr) {
	  ktp::logSDLError("SDL_CreateWindow");
    return false;
	}
  event_bus_.postEvent(kuge::EventTypes::SDL2_MainWindowCreated);

  renderer_ = SDL_CreateRenderer(main_window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer_ == nullptr) {
    ktp::logSDLError("SDL_CreateRenderer");
    return false;
  }
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_RenderSetLogicalSize(renderer_, kSCREEN_SIZE_.x, kSCREEN_SIZE_.y);
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
  if (!TTF_WasInit() && TTF_Init() != 0) {
    ktp::logSDLError("TTF_Init");
    return false;
  }
  if (!ktp::SDL2_Music::initMixer()) return false;

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
  // SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0xFF, 0x00);
  SDL_RenderClear(renderer_);
  texture_jpg_.render({0, 0});
  texture_png_.render({texture_jpg_.getWidth(), 0});
  texture_text_blended_.render({texture_png_.getWidth() * 2, 0});
  texture_text_shaded_.render({texture_png_.getWidth() * 2, texture_text_blended_.getHeight()});
  texture_text_solid_.render({texture_png_.getWidth() * 2, texture_text_blended_.getHeight() + texture_text_shaded_.getHeight()});
  SDL_RenderPresent(renderer_);
}

void Game::update() {
  const float delta_time = clock_.restart() / 1000.f;
  event_bus_.processEvents();
}

void Game::clean() {
  ktp::cleanup(renderer_, main_window_);
  ktp::SDL2_Music::closeMixer();
  if (TTF_WasInit()) TTF_Quit();
  IMG_Quit();
	SDL_Quit();
  event_bus_.postEvent(kuge::EventTypes::GameCleaned);
}
