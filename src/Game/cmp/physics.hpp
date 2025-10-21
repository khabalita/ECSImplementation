#pragma once
#include <cstdint>
#include <ECS/cmp/component.hpp>

// patron Curiously Recurring Template Patter (CRTP)
struct PhysicsComponent_t : public ECS::ComponentBase_t<PhysicsComponent_t>{
    //evita que se produzcan conversiones de tipo implicitas
    explicit PhysicsComponent_t(ECS::EntityID_t eid) 
        : ComponentBase_t(eid)
    {};
    
    float posX { 0.0f }, posY { 0.0f };
    float velX { 0.0f }, velY { 0.0f }; 
};
