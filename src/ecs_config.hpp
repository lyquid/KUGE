#ifndef KUGE_ECS_CONFIG_HPP_
#define KUGE_ECS_CONFIG_HPP_

#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace kuge {
namespace ECS {
// Component
class ComponentArrayInterface;
using ComponentID = std::uint8_t;
constexpr inline ComponentID kMaxComponents {32};
using Signature   = std::bitset<kMaxComponents>;
// Entity
class EntityManager;
using EntityID   = std::uint32_t;
using MapIndex   = EntityID;
using IDsQueue   = std::queue<EntityID>;
constexpr inline EntityID kMaxEntities {5000};
using Signatures = std::array<Signature, kMaxEntities + 1>;
// Component maps
using EntityToIndexMap = std::unordered_map<EntityID, MapIndex>;
using IndexToEntityMap = std::unordered_map<MapIndex, EntityID>;
// ComponentManager
class ComponentManager;
using ComponentToIDMap    = std::unordered_map<const char*, ComponentID>;
using ComponentToArrayMap = std::unordered_map<const char*, std::shared_ptr<ComponentArrayInterface>>;
// SystemManager
class System;
class SystemManager;
using EntitiesSet          = std::unordered_set<EntityID>;
using SystemToSignatureMap = std::unordered_map<const char*, Signature>;
using SystemToPointerMap   = std::unordered_map<const char*, std::shared_ptr<System>>;
// Manager
using ComponentManagerPtr = std::unique_ptr<ComponentManager>;;
using EntityManagerPtr    = std::unique_ptr<EntityManager>;
using SystemManagerPtr    = std::unique_ptr<SystemManager>;

} // end namespace ECS
} // end namespace kuge

#endif // KUGE_ECS_CONFIG_HPP_
