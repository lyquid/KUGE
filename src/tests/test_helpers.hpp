#ifndef KUGE_TESTS_HELPERS_HPP_
#define KUGE_TESTS_HELPERS_HPP_

#include "../ecs_manager.hpp"
#include <gtest/gtest.h>
#include <vector>

namespace kuge {
namespace Tests {

struct Vec2 {
  float x {};
  float y {};
};

struct GravityComponent { Vec2 g {0.f, 9.8f}; };

struct TransformComponent {
  Vec2 position {42.f, 23.4f};
  float rotation {90.f};
  float scale {1.f};
};

struct RigidBodyComponent {
	float velocity {300000.f};
	Vec2 acceleration {3.14f, 34.f};
};

struct RenderComponent {
  std::vector<Vec2> points {};
};

class PhysicsSystem: public ECS::System {
 public:
  void update(ECS::Manager& manager, float delta_time = 0.1f) {
    for (auto entity: m_entities) {
      auto gravity {manager.component<GravityComponent>(entity)};
      auto rigidB {manager.component<RigidBodyComponent>(entity)};
      auto transf {manager.component<TransformComponent>(entity)};
      transf.position = {
        transf.position.x * rigidB.velocity * rigidB.acceleration.x + gravity.g.x * delta_time,
        transf.position.y * rigidB.velocity * rigidB.acceleration.y + gravity.g.y * delta_time
      };
    }
  }
};

class RenderSystem: public ECS::System {
 public:
  void update(ECS::Manager& manager) {
    for (auto entity: m_entities) {
      // render!
    }
  }
};

template<typename T>
auto isEmpty(const T& container) {
  return container.empty() ? testing::AssertionSuccess() << "Container is empty." : testing::AssertionFailure() << "Container is not empty.";
}

template<typename T>
auto isNullptr(T pointer) {
  return pointer == nullptr ? testing::AssertionSuccess() << "Pointer is nullptr." : testing::AssertionFailure() << "Pointer is not nullptr.";
}

template<typename T>
auto isNullptr(const T& pointer) {
  return pointer == nullptr ? testing::AssertionSuccess() << "Pointer is nullptr." : testing::AssertionFailure() << "Pointer is not nullptr.";
}

} } // namespace Tests/kuge

#endif // KUGE_TESTS_HELPERS_HPP_
