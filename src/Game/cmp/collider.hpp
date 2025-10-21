#pragma once
#include <cstdint>
#include <ECS/cmp/component.hpp>

struct ColliderComponent_t : public ECS::ComponentBase_t<ColliderComponent_t> {
    explicit ColliderComponent_t(ECS::EntityID_t eid)
        :ComponentBase_t(eid)
    {}
    
    // Offsets desde el origen del sprite (0,0)
    uint32_t xLeft;
    uint32_t xRight;
    uint32_t yUp;
    uint32_t yDown;

    // Ancho y Alto de la caja
    uint32_t Box;
    uint32_t hBox;
};