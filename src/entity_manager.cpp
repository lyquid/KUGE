#include "entity_manager.hpp"

using namespace kuge;

EntityManager::EntityManager() {
  for (EntityID i = 1; i <= k_max_entities; ++i) {
    m_ids_carousel.push(i);
  }
}

EntityManager::EntityID EntityManager::createEntity() {
  if (m_entities_count == k_max_entities) return 0;
  const auto current_id {m_ids_carousel.front()};
  m_ids_carousel.pop();
  ++m_entities_count;
  return current_id;
}

void EntityManager::destroyEntity(EntityID id) {
  // something
  m_ids_carousel.push(id);
  --m_entities_count;
}
