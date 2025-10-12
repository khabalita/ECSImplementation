#include <util/keyboard.hpp>
#include <raylib.h>

namespace ECS
{
    
void
Keyboard_t::updateState() noexcept{
    //1- Recorrer la enumeracion de Raylib
    //Lo mas eficiente es iterar sobre todo el rango de teclas que raylib define
    for (int key=0; key < key_states.size(); key++){
        //usa CheckKeyPressed() o IsKeyDown() dependiendo si queres un evento de un solo frame o el estado mantenido
        key_states[key] = IsKeyDown(key);

        //Se podrian usar dos array distintos: uno para "down" y otro para "pressed"
    }
}


} // namespace ECS
