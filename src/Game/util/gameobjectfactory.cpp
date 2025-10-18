#include <Game/util/gameobjectfactory.hpp>
#include <ECS/man/resourcemanager.hpp>
#include <iostream>

ECS::Entity_t&
GameObjectFactory_t::createEntity(uint32_t x, uint32_t y, const std::string_view filename) const {
    auto& entity   = m_EntMan.createEntity();
    auto& ren      = m_EntMan.addComponent<RenderComponent_t>(entity, m_ResMan, std::string(filename));
    auto& phy      = m_EntMan.addComponent<PhysicsComponent_t>(entity);
    auto& col      = m_EntMan.addComponent<ColliderComponent_t>(entity);
    ren.w = ren.texture->width;
    ren.h = ren.texture->height;
    phy.posX = x; phy.posY = y;
    col.box.xLeft   = 0;
    col.box.xRight  = ren.w;
    col.box.yUp     = 0;
    col.box.yDown   = ren.h;

    std::cout << "[GameObjectFactory] Entidad creada en (" << x << ", " << y
              << ") con textura: " << filename << " | Tamaño: " << ren.w << "x" << ren.h << "\n";

    return entity;
}

ECS::Entity_t&
GameObjectFactory_t::createPlayer(uint32_t x, uint32_t y) const {
    auto& entity = createEntity(x, y, "assets/texture/PinkDude.png");
    m_EntMan.addComponent<InputComponent_t>(entity);
    return entity;
}