#pragma once
#include <ECS/util/typealiases.hpp>

template <typename GameCTX_t>
struct PhysicsSystem_t {
    //al hacer un constructor por default no hace falta declarar un destructor
    explicit PhysicsSystem_t() = default;

    void update(GameCTX_t& g, float delta) const;
    
};



