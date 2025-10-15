#include <Game/sys/collision.hpp>
#include <Game/cmp/physics.hpp>
#include <Game/cmp/collider.hpp>

template <typename GameCTX_t>
CollisionSystem_t<GameCTX_t>::CollisionSystem_t(uint32_t w, uint32_t h)
    : m_w(w), m_h(h)
{}

template <typename GameCTX_t>
bool
CollisionSystem_t<GameCTX_t>::update(GameCTX_t& g) const {
    for (auto& col : g.template getComponents<ColliderComponent_t>()) {
        auto* phy = g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(col);
        if(!phy) continue;

        // convierte las coordenadas de sprites en coordenadas de pantalla
        auto xL { phy->posX + col.box.xLeft  };
        auto xR { phy->posX + col.box.xRight };
        auto yU { phy->posY + col.box.yUp    };
        auto yD { phy->posY + col.box.yDown  };

        // colisiones
        if(xL > m_w || xR > m_w) { phy->posX -= phy->velX; phy->posX = -phy->velX; }
        if(yU > m_w || yD > m_w) { phy->posY -= phy->velY; phy->posY = -phy->velY; }
    }
    return true;
}

