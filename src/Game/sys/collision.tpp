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

        // Convierte las coordenadas de sprites en coordenadas de pantalla
        auto xL { phy->posX + col.boxRoot.box.xLeft  }; //xL --> xLeft
        auto xR { phy->posX + col.boxRoot.box.xRight }; //xR --> xRight
        auto yU { phy->posY + col.boxRoot.box.yUp    }; //yU --> yUp
        auto yD { phy->posY + col.boxRoot.box.yDown  }; //yD --> yDown

        if (xL < 0) {
            // Reajusta posX para que el borde izquierdo (xL) quede exactamente en 0
            phy->posX -= xL; 
            phy->velX = 0;
        }

        if (xR > m_w) {
            // Reajusta posX para que el borde derecho (xR) quede exactamente en m_w
            phy->posX -= (xR - m_w);
            phy->velX = 0;
        }

        if (yU < 0) {
            phy->posY -= yU;
            phy->velY = 0;
        }

        if (yD > m_h) {
            phy->posY -= (yD - m_h);
            phy->velY = 0;
        }
    }
    return true;
}

