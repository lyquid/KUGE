#include "../ecs_manager.hpp"
#include "test_helpers.hpp"
#include <gtest/gtest.h>

using namespace kuge::ECS;
using namespace kuge::Tests;

// COMPONENT ARRAY

TEST(ComponentArrayDeathTests, data) {
  Manager manager {};
  const auto entity_id {manager.createEntity()};
  ASSERT_DEATH(manager.component<TransformComponent>(entity_id), "Assertion failed") << "Assertion should fail if trying to retrieve a non-existent component's data.";
}

TEST(ComponentArrayDeathTests, insert) {
  Manager manager {};
  const auto entity_id {manager.createEntity()};
  manager.registerComponent<RigidBodyComponent>();
  manager.addComponent(entity_id, RigidBodyComponent{});
  ASSERT_DEATH(manager.addComponent(entity_id, RigidBodyComponent{}), "Assertion failed") << "Assertion should fail if entity already has that component.";
}

TEST(ComponentArrayDeathTests, remove) {
  Manager manager {};
  const auto entity_id {manager.createEntity()};
  manager.registerComponent<RigidBodyComponent>();
  ASSERT_DEATH(manager.removeComponent<RigidBodyComponent>(entity_id) , "Assertion failed") << "Assertion should fail if trying to remove a non-existent component.";
}

// COMPONENT MANAGER

TEST(ComponentManagerDeathTests, addComponent) {
  Manager manager {};
  const auto entity {manager.createEntity()};
  ASSERT_DEATH(manager.addComponent(entity, RenderComponent{}) , "Assertion failed") << "Assertion should fail if trying to add a component that is not registered.";
}

TEST(ComponentManagerDeathTests, component) {
  Manager manager {};
  const auto entity {manager.createEntity()};
  ASSERT_DEATH(manager.component<RenderComponent>(entity), "Assertion failed") << "Assertion should fail if trying to get a component which is not registered.";
}

TEST(ComponentManagerDeathTests, componentID) {
  Manager manager {};
  ASSERT_DEATH(manager.componentID<RenderComponent>(), "Assertion failed") << "Assertion should fail if trying to get a component ID which is not registered.";
}

TEST(ComponentManagerDeathTests, removeComponent) {
  Manager manager {};
  const auto entity {manager.createEntity()};
  ASSERT_DEATH(manager.removeComponent<RenderComponent>(entity) , "Assertion failed") << "Assertion should fail if trying to remove a component that is not even registered.";
  manager.registerComponent<RenderComponent>();
  manager.addComponent(entity, RenderComponent{});
  manager.removeComponent<RenderComponent>(entity);
  ASSERT_DEATH(manager.removeComponent<RenderComponent>(entity) , "Assertion failed") << "Assertion should fail if trying to remove a component not owned by the entity.";
}

TEST(ComponentManagerDeathTests, registerComponent) {
  Manager manager {};
  manager.registerComponent<RenderComponent>();
  ASSERT_DEATH(manager.registerComponent<RenderComponent>(), "Assertion failed") << "Assertion should fail if trying to register the same component more than once.";
}

TEST(ComponentManagerTests, addComponent) {
  // must improve this
  Manager manager {};
  const auto entity {manager.createEntity()};
  manager.registerComponent<TransformComponent>();
  manager.addComponent(entity, TransformComponent{});
  const auto angle {manager.component<TransformComponent>(entity).rotation};
  EXPECT_FLOAT_EQ(angle, TransformComponent{}.rotation) << "addComponent should add a component to an entity.";
}

TEST(ComponentManagerTests, component) {
  Manager manager {};
  const auto entity {manager.createEntity()};
  manager.registerComponent<TransformComponent>();
  manager.addComponent(entity, TransformComponent{});
  const auto angle {manager.component<TransformComponent>(entity).rotation};
  EXPECT_FLOAT_EQ(angle, TransformComponent{}.rotation) << "component should retrieve a component of an entity.";
}

TEST(ComponentManagerTests, componentID) {
  Manager manager {};
  manager.registerComponent<RigidBodyComponent>();
  const auto rigidb_id {manager.componentID<RigidBodyComponent>()};
  EXPECT_EQ(rigidb_id, 0) << "First component id should be 0.";
  manager.registerComponent<RenderComponent>();
  const auto render_id {manager.componentID<RenderComponent>()};
  EXPECT_EQ(render_id, 1) << "Second component id should be 1.";
  const auto rigidb_id2 {manager.componentID<RigidBodyComponent>()};
  EXPECT_EQ(rigidb_id, rigidb_id2) << "componentID should return the correct id.";
}

// TEST(ComponentManagerTests, entityDestroyed) {
//   EntityManager entity_manager {};
//   const auto entity {entity_manager.createEntity()};
//   ComponentManager component_manager {};
//   component_manager.registerComponent<Position>();
//   component_manager.registerComponent<Health>();
//   Position pos {};
//   Health hp {};
//   component_manager.addComponent(entity, pos);
//   component_manager.addComponent(entity, hp);
//   component_manager.entityDestroyed(entity);
//   // and now what?
// }

TEST(ComponentManagerTests, registerComponent) {
  Manager manager {};
  manager.registerComponent<RenderComponent>();
  EXPECT_EQ(manager.componentID<RenderComponent>(), 0) << "registerComponent should register components starting with id 0.";
  manager.registerComponent<RigidBodyComponent>();
  EXPECT_EQ(manager.componentID<RigidBodyComponent>(), 1) << "registerComponent should increment the id of the component by 1.";
}

// TEST(ComponentManagerTests, removeComponent) {
//   Manager manager {};
//   manager.registerComponent<RenderComponent>();
//   const auto entity {manager.createEntity()};
//   manager.addComponent(entity, RenderComponent{});
//   manager.removeComponent<RenderComponent>(entity);
//   // how can we test this...
// }
