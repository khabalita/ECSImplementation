#pragma once
#include <cstdint>
#include <ECS/cmp/component.hpp>
#include <ECS/util/typealiases.hpp>

// patron Curiously Recurring Template Patter (CRTP)
struct InputComponent_t : public ECS::ComponentBase_t<InputComponent_t>{
    explicit InputComponent_t(ECS::EntityID_t eid)
        : ComponentBase_t(eid)
    {};

};
