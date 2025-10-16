#pragma once
#include <ECS/util/typealiases.hpp>

// forward declaration
struct SpawnerComponent_t;
struct PhysicsComponent_t;

template <typename GameCTX_t>
struct SpawnerSystem_t {

    explicit SpawnerSystem_t() = default;
    void update(GameCTX_t& g) const;

};