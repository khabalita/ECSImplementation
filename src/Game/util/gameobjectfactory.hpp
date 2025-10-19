#pragma once
#include <string_view>
#include <Game/cmp/collider.hpp>
#include <Game/cmp/input.hpp>
#include <Game/cmp/physics.hpp>
#include <Game/cmp/render.hpp>
#include <Game/cmp/spawner.hpp>
#include <ECS/man/entitymanager.hpp>
#include <ECS/man/resourcemanager.hpp>

// forward declaration
namespace ECS {
    struct EntityManager_t;
    struct Entity_t;
} // namespace ECS

struct GameObjectFactory_t{
    explicit GameObjectFactory_t(ECS::EntityManager_t& em, ECS::ResourceManager_t& res)
        : m_EntMan(em), m_ResMan(res)
    {}

    ECS::Entity_t& createEntity(uint32_t x, uint32_t y, const std::string_view filename) const;
    ECS::Entity_t& createPlayer(uint32_t x, uint32_t y) const;

    template <typename CALLABLE_t>
    ECS::Entity_t& createSpawner(uint32_t x, uint32_t y, CALLABLE_t callback) const {
        auto& entity = m_EntMan.createEntity();
        auto& spw    = m_EntMan.addComponent<SpawnerComponent_t>(entity);
        auto& phy    = m_EntMan.addComponent<PhysicsComponent_t>(entity);
        m_EntMan.addComponent<ColliderComponent_t>(entity);
        phy.posX = x; phy.posY = y;
        phy.velX = 0;

        spw.spawnMethod = callback;
   return entity;
}

private:
    ECS::EntityManager_t& m_EntMan;
    ECS::ResourceManager_t& m_ResMan;
};
