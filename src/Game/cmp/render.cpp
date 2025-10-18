#include <Game/cmp/render.hpp>
#include <ECS/man/resourcemanager.hpp>
#include <iostream>
#include <string_view>

RenderComponent_t::RenderComponent_t(ECS::EntityID_t eid, ECS::ResourceManager_t& rm, const std::string_view& filename)
    :ComponentBase_t(eid), w(32), h(32), texture(nullptr)
    {
        if (!filename.empty()) {
            texture = &rm.getTexture(std::string (filename));
            if (texture && texture->id != 0) {
                w = texture->width;
                h = texture->height;
                std::cout << "[RenderComponent] Textura cargada correctamente: " << filename
                          << " (" << w << "x" << h << ")\n";
            }
        else {
            std::cerr << "[RenderComponent] Sin archivo de textura para entidad ID "
                  << eid << "\n";
        }
        }
    }