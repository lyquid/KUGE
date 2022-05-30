#include "src/entity_manager.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  kuge::EntityManager entitiy_manager {};
  for (auto i = 0; i < 500; ++i) {
    entitiy_manager.createEntity();
  }

  std::cout << "entity count: " << entitiy_manager.entitiesCount() << "\n";
  entitiy_manager.destroyEntity(4);
  std::cout << "entity count: " << entitiy_manager.entitiesCount() << "\n";
  return 0;
}
