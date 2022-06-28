# K.U.G.E

Ketepincho's Unbelievable(Useless) Game Engine.

## Entity Component System

Heavily based in Austin Morlan's [ECS](https://austinmorlan.com/posts/entity_component_system/).

Usage instructions:

1. Create a `Manager` object. It will automatically create the other sub-managers: `ComponentManager`, `EntityManager` and `SystemManager`.

 ```c++
 kuge::ECS::Manager manager {};
 ```

2. Register your Systems:

 ```c++
 manager.registerSystem<PhysicsSystem>();
 manager.registerSystem<RenderSystem>();
 ```

3. Register your Components:

 ```c++
 manager.registerComponent<Transform>();
 manager.registerComponent<RigidBody>();
 ```

4. Generate a signature for each of your Systems. The signature is a `std::bitfield` that informs which Components needs a System to perform it's task. For example:

 ```c++
 kuge::ECS::Signature signature {};
 signature.set(manager.componentID<Gravity>(), true);
 signature.set(manager.componentID<Transform>(), true);
 signature.set(manager.componentID<RigidBody>(), true);
 manager.setSystemSignature<PhysicsSystem>(signature);
 ```

 > **Pro tip**: use Manager's `systemSignature<T>()` to retrieve a System's signature.

5. Create some entities:

 ```c++
 auto entity {manager.createEntity()};
 ```

6. Add the desired Components to your Entities :

 ```c++
 manager.addComponent(entity, Transform{});
 ```

7. On your update loop `update()` the Systems:

 ```c++
 manager.system<PhysicsSystem>()->update();
 ```

8. Hopefully enjoy!
