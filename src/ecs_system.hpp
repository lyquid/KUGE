#ifndef KUGE_ECS_SYSTEM_HPP_
#define KUGE_ECS_SYSTEM_HPP_

#include "ecs_config.hpp"
#include <typeinfo>

namespace kuge { namespace ECS {

/**
 * @brief An interface class for Systems.
 */
class System {
  friend class SystemManager;
 protected:
  // The enities that have business with this system.
  EntitiesSet m_entities {};
};

/**
 * @brief The manager for the Systems (the logic).
 */
class SystemManager {

  friend class Manager;

 private:

  /**
   * @brief Deletes an entity from all systems' entities sets.
   * @param entity The entity destroyed.
   */
  void entityDestroyed(EntityID entity) {
		for (const auto& pair: m_systems) pair.second->m_entities.erase(entity);
	}

  /**
   * @brief Updates the systems' sets of entities when an entity's signature
   * has changed.
   * @param entity The entity that has changed signature.
   * @param signature The new signature of the entity.
   */
  void entitySignatureChanged(EntityID entity, Signature signature) {
		// Notify each system that an entity's signature changed
		for (const auto& pair: m_systems) {
			const auto& system {pair.second};
			const auto& system_signature {m_signatures[pair.first]};
			// Entity signature matches system signature - insert into set
			if ((signature & system_signature) == system_signature) {
				system->m_entities.insert(entity);
			} else { // Entity signature does not match system signature - erase from set
				system->m_entities.erase(entity);
			}
		}
	}

	/**
	 * @brief Registers a new system.
	 * @tparam T The system to register.
	 * @return A shared_ptr to the new system.
	 */
  template<typename T>
	std::shared_ptr<T> registerSystem() {
		const auto type_name {typeid(T).name()};
		assert(m_systems.find(type_name) == m_systems.end() && "Registering system more than once.");
		auto system {std::make_shared<T>()};
		m_systems.insert({type_name, system});
		return system;
	}

  /**
   * @brief Sets a siganture for a system.
   * @tparam T The system.
   * @param signature The signature.
   */
  template<typename T>
	void setSignature(const Signature& signature) {
		const auto type_name {typeid(T).name()};
		assert(m_systems.find(type_name) != m_systems.end() && "System used before registered.");
    if (!m_signatures.insert({type_name, signature}).second) {
      // changing the signature of a system, strange
      m_signatures[type_name] = signature;
      // change more things

    }
	}

  // System type string -> signature
	SystemToSignatureMap m_signatures {};
	// System type string -> system pointer
	SystemToPointerMap m_systems {};
};

} } // end namespace ECS/kuge

#endif // KUGE_ECS_SYSTEM_HPP_
