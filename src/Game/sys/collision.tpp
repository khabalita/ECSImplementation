#include <Game/sys/collision.hpp>
// e  --> entity
//phy --> physics
//ren --> render
template <typename GameCTX_t>
bool
CollisionSystem_t<GameCTX_t>::update(GameCTX_t& g) const {
    for (auto& e : g.getEntities()) {
        auto* phy = e.template getComponent<PhysicsComponent_t>();
        auto* ren = e.template getComponent<RenderComponent_t>();
        //compruebo colision en X
        if(phy && ren){
            if(phy->posX < 640 || phy->posX + ren->w > 640)
            {
                phy->velY -= phy->velX; 
                phy->velX = -phy->velX;
            };
            //compruebo colision en Y
            if(phy->posY < 360 || phy->posY + ren->h > 360)
            {
                phy->posY -= phy->velY; 
                phy->velY = -phy->velY;
            };
        }
    }
    return true;
}

