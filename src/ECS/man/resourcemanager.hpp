#pragma once
#include <string>
#include <raylib.h>
#include <unordered_map>

namespace ECS {
    
struct ResourceManager_t{
    //constructor por defecto
    ResourceManager_t() = default;
    //destructor
    ~ResourceManager_t();

    //borrado de funciones de asignacion y operadores
    ResourceManager_t(const ResourceManager_t&) = delete;
    ResourceManager_t(ResourceManager_t&&) = delete;
    ResourceManager_t& operator=(const ResourceManager_t&) = delete;
    ResourceManager_t& operator=(ResourceManager_t&&) = delete;

    Texture2D& getTexture(const std::string& filename);

private:
    std::unordered_map<std::string, Texture2D> m_texture;
};

} // namespace ECS

