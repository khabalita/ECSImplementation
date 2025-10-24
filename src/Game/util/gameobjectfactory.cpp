#include <Game/util/gameobjectfactory.hpp>
#include <Game/data/metadata.hpp>
#include <ECS/man/resourcemanager.hpp>

#include <iostream>

extern ColliderMetadataMap metadata_map;

ECS::Entity_t&
GameObjectFactory_t::createEntity(uint32_t x, uint32_t y, 
                                  const std::string_view texturePath,
                                  const std::string_view jsonKey) const 
{
    auto& entity   = m_EntMan.createEntity();
    
    // 1. CARGA DE TEXTURA: Usa el path COMPLETO. Resuelve el error de Raylib.
    auto& ren      = m_EntMan.addComponent<RenderComponent_t>(entity, m_ResMan, std::string(texturePath));
    auto& phy      = m_EntMan.addComponent<PhysicsComponent_t>(entity);
    
    ren.w = ren.texture->width;
    ren.h = ren.texture->height;
    phy.posX = x; phy.posY = y;

    // 2. INYECCIÓN DEL COLLIDER: Usa solo la clave JSON. Resuelve la búsqueda de metadatos.
    
    auto& col = m_EntMan.addComponent<ColliderComponent_t>(entity);

    if (metadata_map.count(std::string(jsonKey))) {
        
        const auto& bounds = metadata_map.at(std::string(jsonKey));
        
        col.xLeft   = bounds.xLeft;
        col.xRight  = bounds.xRight;
        col.yUp     = bounds.yUp;
        col.yDown   = bounds.yDown;
        
        std::cout << "[GameObjectFactory] Collider ajustado para: " << jsonKey << "\n";
        
    } else {
        
        col.xLeft   = 0;
        col.xRight  = ren.w;
        col.yUp     = 0;
        col.yDown   = ren.h;
        
        std::cerr << "[GameObjectFactory] ADVERTENCIA: Metadatos NO encontrados para clave: " << jsonKey 
                  << ". Usando BBox completo.\n";
    }
    
    std::cout << "[GameObjectFactory] Entidad creada en (" << x << ", " << y
              << ") con textura: " << texturePath << "\n";

    return entity;
}

ECS::Entity_t&
GameObjectFactory_t::createPlayer(uint32_t x, uint32_t y) const {
    
    // Ruta que Raylib usa para cargar (path completo)
    const std::string path = "assets/texture/Player.png"; 
    
    // Clave que se usa para buscar en el JSON (solo nombre base)
    const std::string jsonKey = "Player"; 

    // Llamamos a createEntity con AMBOS parámetros
    auto& entity = createEntity(x, y, path, jsonKey); 
    
    // Añadimos componentes específicos del jugador
    m_EntMan.addComponent<InputComponent_t>(entity);
    
    return entity;
}