#include <Game/sys/movement.hpp>
#include <Game/cmp/physics.hpp>
#include <Game/cmp/input.hpp>

template <typename GameCTX_t>
void MovementSystem_t<GameCTX_t>::update(GameCTX_t& g, float delta) const {
    const float SPEED = 100.0f;

    for (auto& entity : g.getEntities()) {
        auto* input = entity.template getComponent<InputComponent_t>();
        auto* phy = entity.template getComponent<PhysicsComponent_t>();

        if(!input || !phy) continue;

        phy->velX = 0.0f;
        phy->velY = 0.0f;

        if (input->moveRight) phy->velX = SPEED;
        if (input->moveLeft)  phy->velX = -SPEED;
        if (input->moveUp)    phy->velY = -SPEED;
        if (input->moveDown)  phy->velY = SPEED;
    }
}