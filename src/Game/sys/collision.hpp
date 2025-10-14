#pragma once
#include <ECS/util/typealiases.hpp>

// Forward Declaration
struct ColliderComponent_t;

template <typename GameCTX_t>
struct CollisionSystem_t {

    explicit CollisionSystem_t(uint32_t w, uint32_t h);

    PhysicsComponent_t* getRequiredComponent(GameCTX_t& g, const ColliderComponent_t& col) const;

    bool update(GameCTX_t& g) const;

private:
    //las variables ancho y alto de pantalla no van a cambiar en ejecucion, por eso const
    const uint32_t m_w { 0 }, m_h { 0 };
    
};