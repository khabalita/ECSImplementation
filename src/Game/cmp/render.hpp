#pragma once
#include <cstdint>
#include <vector>
#include <raylib.h>
#include <ECS/cmp/component.hpp>
#include <ECS/util/typealiases.hpp>
#include <ECS/man/resourcemanager.hpp>

// patron Curiously Recurring Template Patter (CRTP)
struct RenderComponent_t : public ECS::ComponentBase_t<RenderComponent_t>{
    explicit RenderComponent_t(ECS::EntityID_t eid)
        : ComponentBase_t(eid)
    {};

    explicit RenderComponent_t(ECS::EntityID_t eid, ECS::ResourceManager_t& rm, std::string filename = "");

    //volver a mirar video 33 y 34
    
    uint32_t w { 0 }, h { 0 }; // tamaño, enteros de 32 bits, inicializados en 0
    bool hasTexture { false };
    Texture2D* texture { nullptr};
    Color color;

};