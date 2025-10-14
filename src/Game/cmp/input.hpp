#pragma once
#include <cstdint>
#include <ECS/cmp/component.hpp>
#include <ECS/util/typealiases.hpp>
#include <raylib.h>

// patron Curiously Recurring Template Patter (CRTP)
struct InputComponent_t : public ECS::ComponentBase_t<InputComponent_t>{
    explicit InputComponent_t(ECS::EntityID_t eid)
        : ComponentBase_t(eid)
    {};

    bool moveLeft   { false };
    bool moveRight  { false };
    bool moveUp     { false };
    bool moveDown   { false };
    bool action     { false }; 

};
