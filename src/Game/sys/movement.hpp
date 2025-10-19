#pragma once
#include <Game/cmp/input.hpp>
#include <Game/cmp/physics.hpp>
#include <ECS/util/typealiases.hpp>

template <typename GameCTX_t>
struct MovementSystem_t{
    explicit MovementSystem_t() = default;

    void update(GameCTX_t& g, float delta) const;
};