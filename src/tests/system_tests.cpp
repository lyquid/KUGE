#include "../ecs_manager.hpp"
#include "test_helpers.hpp"
#include <gtest/gtest.h>

using namespace kuge::ECS;
using namespace kuge::Tests;

// TEST(SystemManagerDeathTests, entityDestroyed) {}

// TEST(SystemManagerDeathTests, entitySignatureChanged) {}

TEST(SystemManagerDeathTests, registerSystem) {
  Manager manager {};
  manager.registerSystem<PhysicsSystem>();
  ASSERT_DEATH(manager.registerSystem<PhysicsSystem>(), "Assertion failed") << "Assertion should fail if trying to register the same System more than once.";
}

TEST(SystemManagerDeathTests, setSignature) {
  Manager manager {};
  const Signature sig {};
  ASSERT_DEATH(manager.setSystemSignature<PhysicsSystem>(sig), "Assertion failed") << "Assertion should fail if trying to use a System before registering it.";
}

TEST(SystemManagerTests, registerSystem) {
  Manager manager {};
  manager.registerSystem<PhysicsSystem>();
  // and?
}

TEST(SystemManagerTests, setSignature) {
  Manager manager {};
  manager.registerSystem<PhysicsSystem>();
  manager.registerSystem<RenderSystem>();
  // register some components to play with
  manager.registerComponent<GravityComponent>();
  manager.registerComponent<RigidBodyComponent>();
  manager.registerComponent<TransformComponent>();
  manager.registerComponent<RenderComponent>();
  // signature for physics system
  Signature signature {};
  signature.set(manager.componentID<GravityComponent>(), true);
  signature.set(manager.componentID<RigidBodyComponent>(), true);
  signature.set(manager.componentID<TransformComponent>(), true);
  manager.setSystemSignature<PhysicsSystem>(signature);
  // signature for render system
  signature.reset();
  signature.set(manager.componentID<RenderComponent>(), true);
  manager.setSystemSignature<RenderSystem>(signature);
  // test for difference
  EXPECT_NE(manager.systemSignature<PhysicsSystem>(), manager.systemSignature<RenderSystem>()) << "setSignature should set correct signatures to Systems.";
  // make signatures the same
  signature = manager.systemSignature<PhysicsSystem>();
  manager.setSystemSignature<RenderSystem>(signature);
  // test for equality
  EXPECT_EQ(manager.systemSignature<PhysicsSystem>(), manager.systemSignature<RenderSystem>()) << "setSignature should set correct signatures to Systems.";
}
