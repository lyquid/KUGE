#ifndef KUGE_ECS_COMPONENT_HPP_
#define KUGE_ECS_COMPONENT_HPP_

#include "ecs_config.hpp"
#include <typeinfo>

namespace kuge { namespace ECS {

/**
 * @brief Interface for the ComponentArray template class.
 */
class ComponentArrayInterface {
 public:
	virtual ~ComponentArrayInterface() = default;
	virtual void entityDestroyed(EntityID entity) = 0;
};

/**
 * @brief An array-like container for components with a common interface.
 * @tparam T A component type.
 */
template<typename T>
class ComponentArray: public ComponentArrayInterface {

  friend class ComponentManager;

 private:

  /**
   * @brief Access the component's data.
   * @param entity The entity owner of the component.
   * @return A reference to the component.
   */
  T& data(EntityID entity) {
		assert(m_entity_to_index.find(entity) != m_entity_to_index.end() && "Retrieving non-existent component.");
		return m_components[m_entity_to_index[entity]];
	}

  /**
   * @brief Checks if a destroyed entity has a component here and, if so,
   * it calls remove on it.
   * @param entity The entity destroyed.
   */
  void entityDestroyed(EntityID entity) override {
    if (m_entity_to_index.find(entity) != m_entity_to_index.end()) remove(entity);
  }

  /**
   * @brief Adds a component to an entity.
   * @param entity The entity to add the component to.
   * @param component The component to add.
   */
  void insert(EntityID entity, const T& component) {
    assert(m_entity_to_index.find(entity) == m_entity_to_index.end() && "Component added to same entity more than once");
    m_components[m_index] = component; // make moveable?
		m_entity_to_index[entity] = m_index;
		m_index_to_entity[m_index] = entity;
		++m_index;
	}

  /**
   * @brief Removes the component of the given entity and compacts the array
   * of components.
   * @param entity The entity.
   */
  void remove(EntityID entity) {
		assert(m_entity_to_index.find(entity) != m_entity_to_index.end() && "Removing non-existent component.");
		const auto removed_entity_index {m_entity_to_index[entity]};
		const auto last_element_index {m_index - 1};
		m_components[removed_entity_index] = m_components[last_element_index]; // make moveable

		const auto last_element_entity {m_index_to_entity[last_element_index]};
		m_entity_to_index[last_element_entity] = removed_entity_index;
		m_index_to_entity[removed_entity_index] = last_element_entity;

		m_entity_to_index.erase(entity);
		m_index_to_entity.erase(last_element_index);

		--m_index;
	}

  // Array of componens of type T.
	std::array<T, kMaxEntities + 1> m_components {};
  // Entity id -> component index.
	EntityToIndexMap m_entity_to_index {};
  // Component index -> entity id.
	IndexToEntityMap m_index_to_entity {};
	// Highest index of the array.
	MapIndex m_index {};
};

/**
 * @brief Class that is responsable for registering components and managing
 * the arrays of those.
 */
class ComponentManager {

  friend class Manager;

 private:

  /**
   * @brief Adds a component to a given entity.
   * @tparam T A component type.
   * @param entity The entity to add the component to.
   * @param component The component. The type must have been registered previously.
   */
  template<typename T>
	void addComponent(EntityID entity, T component) {
		componentArray<T>()->insert(entity, component);
	}

  /**
   * @brief Retrieves a reference for an entity's component.
   * @tparam T A component type.
   * @param entity The entity id.
   * @return A reference to the component.
   */
  template<typename T>
	T& component(EntityID entity) {
		return componentArray<T>()->data(entity);
	}

  /**
   * @brief Use this to access the ComponentArray of the requested type.
   * @tparam T A component type.
   * @return A shared_ptr to the requested ComponentArray.
   */
	template<typename T>
	std::shared_ptr<ComponentArray<T>> componentArray() {
		const auto component_name {typeid(T).name()};
		assert(m_component_ids.find(component_name) != m_component_ids.end() && "Component not registered.");
		return std::static_pointer_cast<ComponentArray<T>>(m_component_arrays[component_name]);
	}

  /**
   * @brief Gets a component's type id.
   * @tparam T A component type.
   * @return The id of the component's type.
   */
  template<typename T>
	auto componentID() {
		const auto component_name {typeid(T).name()};
		assert(m_component_ids.find(component_name) != m_component_ids.end() && "Component not registered.");
		return m_component_ids[component_name];
	}

  /**
   * @brief Broadcasts entity's destruction to every ComponentArray so
   * components from that entity get erased.
   * @param entity The demised entity.
   */
  void entityDestroyed(EntityID entity) const {
		for (const auto& pair: m_component_arrays) pair.second->entityDestroyed(entity);
	}

  /**
   * @brief Registers a new component type to the system.
   * @tparam T A component type.
   */
  template<typename T>
	void registerComponent() {
		const auto component_name {typeid(T).name()};
		assert(m_component_ids.find(component_name) == m_component_ids.end() && "Registering component type more than once.");
		// Add this component type to the component type map
		m_component_ids.insert({component_name, m_component_id});
		// Create a ComponentArray pointer and add it to the component arrays map
		m_component_arrays.insert({component_name, std::make_shared<ComponentArray<T>>()});
		// Increment the value so that the next component registered will be different
		++m_component_id;
	}

  /**
   * @brief Removes an entity's component from the corresponding ComponentArray.
   * @tparam T A component type.
   * @param entity The entity owning the component.
   */
  template<typename T>
	void removeComponent(EntityID entity) {
		componentArray<T>()->remove(entity);
	}

  // Component name -> id.
	ComponentToIDMap m_component_ids {};
	// Component name -> ComponentArray pointer.
	ComponentToArrayMap m_component_arrays {};
	// Ids for components, starting at 0.
	ComponentID m_component_id {};
};

} } // namespace ECS/kuge

#endif // KUGE_ECS_COMPONENT_HPP_
