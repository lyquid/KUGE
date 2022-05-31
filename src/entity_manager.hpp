#ifndef KUGE_ENTITY_MANAGER_HPP_
#define KUGE_ENTITY_MANAGER_HPP_

#include <cstdint>
#include <queue>

namespace kuge {

class EntityManager {

  using EntityID = std::uint64_t;
  using IDsQueue = std::queue<EntityID>;

 public:

  EntityManager();
  EntityID createEntity();
  void destroyEntity(EntityID id);
  auto entitiesCount() const { return m_entities_count; }

 private:

  const EntityID k_max_entities {5000};
  IDsQueue m_ids_carousel {};
  EntityID m_entities_count {};
};


} // end namespace kuge

#endif // KUGE_ENTITY_MANAGER_HPP_
