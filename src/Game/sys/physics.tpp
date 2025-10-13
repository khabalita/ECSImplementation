#include <Game/cmp/physics.hpp>

template <typename GameCTX_t>
bool 
PhysicsSystem_t<GameCTX_t>::update(GameCTX_t& g) const {
    for (auto& phy: g.template getComponents<PhysicsComponent_t>()) {
        phy.posX += phy.velX;
        phy.posY += phy.velY;
    }
    return true;
}
