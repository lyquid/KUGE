#ifndef KUGE_ECS_MANAGER_HPP_
#define KUGE_ECS_MANAGER_HPP_

#include "ecs_component.hpp"
#include "ecs_config.hpp"
#include "ecs_entity.hpp"
#include "ecs_system.hpp"

namespace kuge { namespace ECS {

/**
 * @brief The one and only manager for the ECS system!
 */
class Manager {
 public:

  /**
   * @brief Constructs a new Manager and it's subordinate managers.
   */
  Manager():
    m_component_manager(std::make_unique<ComponentManager>()),
    m_entity_manager(std::make_unique<EntityManager>()),
    m_system_manager(std::make_unique<SystemManager>()) { }

  // COMPONENTS

  /**
   * @brief Adds a Component to an entity. It also updates the signatures accordingly.
   * @tparam T A previously registered Component type.
   * @param entity The entity you want to add the Component to.
   * @param component The Component to add.
   */
  template<typename T>
	void addComponent(EntityID entity, T component) {
		m_component_manager->addComponent<T>(entity, component);
		auto signature {m_entity_manager->signature(entity)};
		signature.set(m_component_manager->componentID<T>(), true);
		m_entity_manager->setSignature(entity, signature);
		m_system_manager->entitySignatureChanged(entity, signature);
	}

  /**
   * @brief Access a component type of a given entity, if found.
   * @tparam T A Component type.
   * @param entity The entity owning the Component.
   * @return T& A reference to the requested Component.
   */
  template<typename T>
  T& component(EntityID entity) { return m_component_manager->component<T>(entity); }

  /**
   * @brief Retrieves the ID of a given Component type.
   * @tparam T A component type.
   * @return ComponentID The ID of the requested Component type.
   */
  template<typename T>
  ComponentID componentID() { return m_component_manager->componentID<T>(); }

  /**
   * @brief Registers a new Component type.
   * @tparam T The type of the new Component.
   */
  template<typename T>
  void registerComponent() { m_component_manager->registerComponent<T>(); }

  /**
   * @brief Removes a Component from an entity.
   * @tparam T The Component type.
   * @param entity The entity to remove the Component from.
   */
  template<typename T>
  void removeComponent(EntityID entity) {
    m_component_manager->removeComponent<T>(entity);
    auto signature {m_entity_manager->signature(entity)};
    signature.set(m_component_manager->componentID<T>(), false);
    m_entity_manager->setSignature(entity, signature);
    m_system_manager->entitySignatureChanged(entity, signature);
  }

  // ENTITIES

  /**
   * @brief Creates a new Entity.
   * @return The EntityID or 0 if maximun entities reached.
   */
  EntityID createEntity() { return m_entity_manager->createEntity(); }

  /**
   * @brief Destroys an entity. It's id goes back to the pool, components get
   * erased and it's removed from the entities sets of the corresponding systems.
   * @param entity The entity to destroy.
   */
  void destroyEntity(EntityID entity) {
    m_entity_manager->destroyEntity(entity);
    m_component_manager->entityDestroyed(entity);
    m_system_manager->entityDestroyed(entity);
  }

  /**
   * @return The number of entities currently active.
   */
  auto entitiesCount() const { return m_entity_manager->m_entities_count; }

  /**
   * @brief Use this to know an entity's signature (which components has).
   * @param entity The entity.
   * @return The signature of the given entity.
   */
  auto entitySignature(EntityID entity) const { return m_entity_manager->m_signatures[entity]; }

  /**
   * @return The maximun entities allowed.
   */
  static constexpr auto maxEntities() { return kMaxEntities; }

  // SYSTEMS

  /**
   * @brief Registers a new System.
   * @tparam T The System's type.
   * @return A std::shared_ptr to the newly registered system.
   */
  template<typename T>
  auto registerSystem() { return m_system_manager->registerSystem<T>(); }

  /**
   * @brief Access a previously registered System.
   * @tparam T The System's type.
   * @return A std::shared_pointer to the System.
   */
  template<typename T>
  auto system() { return std::static_pointer_cast<T>(m_system_manager->m_systems[typeid(T).name()]); }

  /**
   * @brief Sets a System's signature, so we know which Components it uses/needs.
   * @tparam T The System's type.
   * @param signature The new signature for the System.
   */
  template<typename T>
  void setSystemSignature(Signature signature) { m_system_manager->setSignature<T>(signature); }

  /**
   * @brief Retrieves a System's signature.
   * @tparam T The System's type.
   * @return The signature of the requested System.
   */
  template<typename T>
  auto systemSignature() { return m_system_manager->m_signatures[typeid(T).name()]; }

 private:

  // A std::unique_ptr to the ComponentManager
  ComponentManagerPtr m_component_manager;
  // A std::unique_ptr to the EntityManager
	EntityManagerPtr    m_entity_manager;
  // A std::unique_ptr to the SystemManager
	SystemManagerPtr    m_system_manager;
};

} } // end namespaces ECS/kuge

#endif // KUGE_ECS_MANAGER_HPP_
