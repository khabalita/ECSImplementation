#include <Game/util/gameobjectfactory.hpp>

ECS::Entity_t&
GameObjectFactory_t::createEntity(uint32_t x, uint32_t y, const std::string_view filename) const {
    auto& entity   = m_EntMan.createEntity();
    auto& ren      = m_EntMan.addComponent<RenderComponent_t>(entity);
    auto& phy      = m_EntMan.addComponent<PhysicsComponent_t>(entity);
    auto& col      = m_EntMan.addComponent<ColliderComponent_t>(entity);
    phy.posX = x; phy.posY = y;
    col.box.xLeft   = 0;
    col.box.xRight  = ren.w;
    col.box.yUp     = 0;
    col.box.yDown   = ren.h;
    return entity;
}

ECS::Entity_t&
GameObjectFactory_t::createPlayer(uint32_t x, uint32_t y) const {
    auto& entity = createEntity(x, y, "aca va el sprite");
    m_EntMan.addComponent<InputComponent_t>(entity);
    return entity;
}