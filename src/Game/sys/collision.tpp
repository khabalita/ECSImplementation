#include <Game/sys/collision.hpp>
// e  --> entity
//phy --> physics
//ren --> render
template <typename GameCTX_t>
bool
CollisionSystem_t<GameCTX_t>::update(GameCTX_t& g) const {
    for(auto& e: g.getEntities()){
        //compruebo colision en X
        if(e.phy && e.ren){
            if(e.phy->posX < 640 || e.phy->posX + e.ren->w > 640)
            {
                e.phy->velY -= e.phy->velX; 
                e.phy->velX = -e.phy->velX;
            };
            //compruebo colision en Y
            if(e.phy->posY < 360 || e.phy->posY + e.ren->h > 360)
            {
                e.phy->posY -= e.phy->velY; 
                e.phy->velY = -e.phy->velY;
            };
        }
    }
}

