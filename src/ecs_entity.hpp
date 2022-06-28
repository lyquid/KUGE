#ifndef KUGE_ECS_ENTITY_HPP_
#define KUGE_ECS_ENTITY_HPP_

#include "ecs_config.hpp"

namespace kuge { namespace ECS {

/**
 * @brief Class responsible of creating new entities by giving them an id and
 * a signature, keep track of how many entities are in use.
 */
class EntityManager {

  friend class Manager;
  // friend class std::unique_ptr<EntityManager>;
  // friend std::unique_ptr<EntityManager> std::make_unique<EntityManager>(EntityManager&);
  // friend std::unique_ptr<EntityManager> std::make_unique<EntityManager>(EntityManager&&);

 public:

  /**
   * @brief Constructs a new EntityManager object.
   */
  EntityManager() noexcept {
    // this should be private bu i'm having problems with unique_ptr construction.
    for (EntityID i = 1; i <= kMaxEntities; ++i) m_id_expender.push(i);
  }

 private:

  /**
   * @brief Creates a new Entity.
   * @return The new entity id or 0 if reached maximun entities.
   */
  EntityID createEntity() {
    if (m_entities_count == kMaxEntities) return static_cast<EntityID>(0);
    const auto current_id {m_id_expender.front()};
    m_id_expender.pop();
    ++m_entities_count;
    return current_id;
  }

  /**
   * @brief Destroys (resets) an entity.
   * @param entity The entity to destroy.
   */
  void destroyEntity(EntityID entity) {
    if (entity <= 0 || entity > kMaxEntities) return;
    m_signatures[entity].reset();
    m_id_expender.push(entity);
    --m_entities_count;
  }

  /**
   * @brief Sets a signature for an entity.
   * @param id of the entity to add the signature to.
   * @param signature The signature you want to add.
   */
  void setSignature(EntityID entity, Signature signature) { m_signatures[entity] = std::move(signature); }

  /**
   * @param id of the entity.
   * @return The signature of a given entity.
   */
  auto signature(EntityID entity) const { return m_signatures[entity]; }

  // Total entities active.
  EntityID m_entities_count {};
  // A pool (queue) of reusable ids for entities.
  IDsQueue m_id_expender {};
  // An array of signatures whose index is the entity.
  Signatures m_signatures {};
};

} } // end namespace ECS/kuge

#endif // KUGE_ECS_ENTITY_HPP_
