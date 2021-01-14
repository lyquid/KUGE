#include "../headers/game.h"

Game::Game():
  quit_(false),
  kFONT_COLOR_({0xFF, 0xFF, 0xFF, 0xFF}),
  kSCREEN_SIZE_({1024u, 768u}),
  clock_(),
  sdl_event_(), 
  font_(nullptr),
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
        quit_ = true;
        input_sys_.postEvent(kuge::EventTypes::ExitGame, "bb...");
        break;
      case SDL_KEYDOWN:
        handleSDLKeyEvents(sdl_event_.key.keysym.sym);
        input_sys_.postEvent(kuge::EventTypes::KeyPressed, 345.7);
        break;
      default:
        break;
    }
  }
}

void Game::handleSDLKeyEvents(const SDL_Keycode& key) {
  switch (key) {
    case SDLK_ESCAPE:
      quit_ = true;
      break;
    case SDLK_SPACE:
      break;
    default:
      break;
  }
}

bool Game::init() {

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    ktp::logSDLError("SDL_Init");
    return false;
  }

  if (TTF_Init() != 0) {
    ktp::logSDLError("TTF_Init");
    SDL_Quit();
    return false;
  }

  main_window_ = SDL_CreateWindow("KUGE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kSCREEN_SIZE_.x, kSCREEN_SIZE_.y, SDL_WINDOW_SHOWN);
  // main_window_ = SDL_CreateWindow("KUGE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
  if (main_window_ == nullptr) {
	  ktp::logSDLError("SDL_CreateWindow");
    TTF_Quit();
    SDL_Quit();
    return false;
	}

  renderer_ = SDL_CreateRenderer(main_window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer_ == nullptr) {
    ktp::logSDLError("SDL_CreateRenderer");
    ktp::cleanup(main_window_);
    TTF_Quit();
    SDL_Quit();
    return false;
  }
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  SDL_RenderSetLogicalSize(renderer_, kSCREEN_SIZE_.x, kSCREEN_SIZE_.y);

  font_ = TTF_OpenFont((ktp::getResourcesPath() + "fonts/Future n0t Found.ttf").c_str(), 18u);
  if (font_ == nullptr) {
    ktp::logSDLError("TTF_OpenFont");
    ktp::cleanup(renderer_, main_window_);
    TTF_Quit();
    SDL_Quit();
    return false;
  }

  event_bus_.postEvent(kuge::EventTypes::InitSuccessfull);
  return true;
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x40, 0x00);
  SDL_RenderClear(renderer_);
  SDL_RenderPresent(renderer_);
}

void Game::update() {

  const float delta_time = clock_.restart() / 1000.f;

  event_bus_.processEvents();
 
}

void Game::clean() {
  //event_bus_.postEvent(kuge::EventTypes::StartedCleanup);
  ktp::cleanup(renderer_, main_window_, font_);
  TTF_Quit();
	SDL_Quit();
  //event_bus_.postEvent(kuge::EventTypes::FinishedCleanup);
}
