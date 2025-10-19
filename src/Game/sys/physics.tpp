#include <Game/cmp/physics.hpp>

template <typename GameCTX_t>
void 
PhysicsSystem_t<GameCTX_t>::update(GameCTX_t& g, float delta) const {
    for (auto& phy: g.template getComponents<PhysicsComponent_t>()) {
        phy.posX += phy.velX * delta;
        phy.posY += phy.velY * delta;
    }
}
