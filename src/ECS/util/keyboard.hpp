#pragma once
#include <raylib.h>
#include <vector>

namespace ECS
{

//constante con el total de teclas admitidas por raylib
constexpr int TOTAL_KEYS = 512;

struct Keyboard_t {
    explicit Keyboard_t() : key_states(TOTAL_KEYS, false) 
    {};

    //Eliminacion de constructores copia y operadores
    Keyboard_t(const Keyboard_t&)              = delete;
    Keyboard_t(Keyboard_t&&)                   = delete;
    Keyboard_t& operator=(const Keyboard_t&)   = delete;
    Keyboard_t& operator=(Keyboard_t&&)        = delete;

    //metodo para obtener el estado de la tecla especifica
    bool isKeyDown(int key) const noexcept {
        if (key >0 && key <= key_states.size()){
            return key_states[key];
        }
        return false;
    }

    void updateState() noexcept;

private:
    //almacena el estado presionado o no, para cada tecla
    std::vector<bool> key_states;
};

} // namespace ECS
