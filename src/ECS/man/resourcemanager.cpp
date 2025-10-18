#include <ECS/man/resourcemanager.hpp>
#include <raylib.h>
#include <memory>

namespace ECS
{

ResourceManager_t::~ResourceManager_t() {
    for (auto & [k, uptr] : m_texture) {
        if (uptr && uptr->id != 0) UnloadTexture(*uptr);
    }
    m_texture.clear();
}

Texture2D& ResourceManager_t::getTexture(const std::string& filename) {
    auto iterator = m_texture.find(filename);
    if(iterator == m_texture.end()){
        //carga la textura si no esta en cache
        Texture2D texture = LoadTexture(filename.c_str());
        if (texture.id == 0)
        {
            throw std::runtime_error("Error al cargar la textura " + filename);
        }
        auto up = std::make_unique<Texture2D>(texture);
        iterator = m_texture.emplace(filename, std::move(up)).first;
    }
    return *iterator->second;
}

const Texture2D& ResourceManager_t::getTexture(const std::string& filename) const {
    auto iterator = m_texture.find(filename);
    if (iterator == m_texture.end()) {
        throw std::runtime_error("Textura no encontrada: " + filename);
    }
    return *iterator->second;
}

} // namespace ECS
