#include <ECS/man/resourcemanager.hpp>
#include <raylib.h>

namespace ECS
{

ResourceManager_t::~ResourceManager_t(){
    for (auto& [filename, texture] : m_texture){
        UnloadTexture(texture);
    }
    m_texture.clear();
}

Texture2D& ResourceManager_t::getTexture(const std::string& filename){
    auto iterator = m_texture.find(filename);
    if(iterator == m_texture.end()){
        //carga la textura si no esta en cache
        Texture2D texture = LoadTexture(filename.c_str());
        if (texture.id == 0)
        {
            throw "Error al cargar la textura " + filename;
        }
        iterator = m_texture.emplace(filename, texture).first;
    }
    return iterator->second;
}

} // namespace ECS
