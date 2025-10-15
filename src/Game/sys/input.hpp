#pragma once
#include <ECS/util/keyboard.hpp>
#include <ECS/man/entitymanager.hpp>
#include <Game/cmp/input.hpp>

template <typename GameCTX_t>
struct InputSystem_t {
    //Constructor explicito
    explicit InputSystem_t(ECS::Keyboard_t& kb)
        : keyboard(kb)
    {}

    void update(GameCTX_t& g) const;

private:
    ECS::Keyboard_t& keyboard;
};