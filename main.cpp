#include "./headers/game.h"

int main(int argc, char* argv[]) {

  Game* game = new Game();

  if (game->init()) {

    while (!game->quit_) {
      game->handleSDLEvents();
      game->update();
      game->render();
    }
    
    delete game;
    return 0;

  } else {
    // something went wrong
    delete game;
    return 1;
  }
}
