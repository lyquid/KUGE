#include "src/ecs_component.hpp"
#include "src/ecs_manager.hpp"
#include "src/ecs_entity.hpp"
#include "src/ecs_system.hpp"
#include "src/tests/test_helpers.hpp"
#include <chrono>
#include <iostream>
#include <numeric> // std::accumulate

using namespace kuge;

int main(int argc, char* argv[]) {
  ECS::Manager manager {};
  // register the systems
  manager.registerSystem<Tests::PhysicsSystem>();
  manager.registerSystem<Tests::RenderSystem>();
  // register components so we can have it's ID (for the bitset)
  manager.registerComponent<Tests::GravityComponent>();
  manager.registerComponent<Tests::TransformComponent>();
  manager.registerComponent<Tests::RigidBodyComponent>();
  manager.registerComponent<Tests::RenderComponent>();
  // make a signature for the systems
  ECS::Signature signature {};
  signature.set(manager.componentID<Tests::GravityComponent>(), true);
  signature.set(manager.componentID<Tests::TransformComponent>(), true);
  signature.set(manager.componentID<Tests::RigidBodyComponent>(), true);
  manager.setSystemSignature<Tests::PhysicsSystem>(signature);
  std::cout << "Signature for physics is:\t" << manager.systemSignature<Tests::PhysicsSystem>() << "\n";
  signature.reset();
  signature.set(manager.componentID<Tests::RenderComponent>(), true);
  manager.setSystemSignature<Tests::RenderSystem>(signature);
  std::cout << "Signature for render is:\t" << manager.systemSignature<Tests::RenderSystem>() << "\n";
  // add components to some entities
  std::vector<ECS::EntityID> entities (ECS::kMaxEntities);
  int i {};
  for (auto& entity: entities) {
    if (i % 2 == 0) {
      entity = manager.createEntity();
      manager.addComponent(entity, Tests::GravityComponent{});
      manager.addComponent(entity, Tests::TransformComponent{});
      if (i % 4 == 0) manager.addComponent(entity, Tests::RigidBodyComponent{(float)i, {}});
      if (i % 3 == 0) manager.addComponent(entity, Tests::RenderComponent{});
      // std::cout << "Entity " << entity << " signature:\t" << manager.entitySignature(entity) << "\n";
    }
    ++i;
  }
  // update system
  constexpr auto loops {1000};
  std::array<unsigned long long, loops> durations {};
  for (int j = 0; j < loops; ++j) {
    const auto start {std::chrono::steady_clock::now()};
    manager.system<Tests::PhysicsSystem>()->update(manager);
    const auto end {std::chrono::steady_clock::now()};
    durations[j] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
  }
  std::cout << "average update time: " << std::accumulate(durations.begin(), durations.end(), 0) / loops << "us.\n";

  return 0;
}
