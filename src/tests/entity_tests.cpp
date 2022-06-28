#include "../ecs_manager.hpp"
#include "test_helpers.hpp"
#include <gtest/gtest.h>

using namespace kuge::ECS;
using namespace kuge::Tests;

TEST(EntityTests, createEntity) {
  Manager manager {};
  const auto entity_id1 {manager.createEntity()};
  EXPECT_EQ(manager.entitiesCount(), 1) << "createEntity should increase the entities count.";
  EXPECT_EQ(entity_id1, 1) << "createEntity should return the id of the new entity.";
  const auto entity_id2 {manager.createEntity()};
  EXPECT_NE(entity_id1, entity_id2) << "New entities should have different ids.";
  for (EntityID i = 0; i < Manager::maxEntities(); ++i) manager.createEntity();
  const auto no_id {manager.createEntity()};
  EXPECT_EQ(no_id, 0) << "createEntity should return 0 if reached entity limit.";
}

TEST(EntityTests, destroyEntity) {
  Manager manager {};
  std::vector<EntityID> entity_ids {};
  for (auto i = 0; i < 10; ++i) entity_ids.push_back(manager.createEntity());
  for (auto id: entity_ids) manager.destroyEntity(id);
  EXPECT_EQ(manager.entitiesCount(), 0) << "destroyEntity should decrease the entity count.";
}

TEST(EntityTests, entitySignature) {
  Manager manager {};
  const auto entity_id {manager.createEntity()};
  Signature signature {};

  manager.registerComponent<GravityComponent>();
  signature.set(manager.componentID<GravityComponent>(), true);
  manager.addComponent(entity_id, GravityComponent{});
  EXPECT_EQ(manager.entitySignature(entity_id), signature) << "entitySignature should return the correct signature.";

  manager.registerComponent<TransformComponent>();
  signature.set(manager.componentID<TransformComponent>(), true);
  manager.addComponent(entity_id, TransformComponent{});
  EXPECT_EQ(manager.entitySignature(entity_id), signature) << "entitySignature should return the correct signature.";

  manager.registerComponent<RigidBodyComponent>();
  signature.set(manager.componentID<RigidBodyComponent>(), true);
  manager.addComponent(entity_id, RigidBodyComponent{});
  EXPECT_EQ(manager.entitySignature(entity_id), signature) << "entitySignature should return the correct signature.";

  manager.registerComponent<RenderComponent>();
  signature.set(manager.componentID<RenderComponent>(), true);
  manager.addComponent(entity_id, RenderComponent{});
  EXPECT_EQ(manager.entitySignature(entity_id), signature) << "entitySignature should return the correct signature.";
}
