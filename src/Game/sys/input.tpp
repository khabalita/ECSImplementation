#include <Game/sys/input.hpp>
#include <raylib.h>

template <typename GameCTX_t>
void
InputSystem_t<GameCTX_t>::update(GameCTX_t& g) const {
    keyboard.updateState();

    for (auto& input : g.template getComponents<InputComponent_t>()) {
        input.moveUp    = keyboard.isKeyDown(KEY_W) || keyboard.isKeyDown(KEY_UP);
        input.moveDown  = keyboard.isKeyDown(KEY_S) || keyboard.isKeyDown(KEY_DOWN);
        input.moveLeft  = keyboard.isKeyDown(KEY_A) || keyboard.isKeyDown(KEY_LEFT);
        input.moveRight = keyboard.isKeyDown(KEY_D) || keyboard.isKeyDown(KEY_RIGHT);
        input.action    = keyboard.isKeyDown(KEY_SPACE);
        
    }
}