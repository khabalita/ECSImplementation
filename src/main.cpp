#include <iostream>
#include <cstdint>
#include <ECS/man/entitymanager.hpp>
#include <Game/sys/render.tpp>
#include <Game/sys/collision.tpp>
#include <Game/sys/input.tpp>
#include <Game/sys/spawn.tpp>
#include <Game/sys/physics.tpp>
#include <Game/sys/movement.tpp>
#include <Game/cmp/collider.hpp>
#include <Game/util/gameobjectfactory.hpp>
#include <Game/data/metadata.hpp>
#include <raylib.h>

constexpr uint32_t kSCRWIDTH  { 640 };
constexpr uint32_t kSCRHEIGHT { 360 };

ColliderMetadataMap metadata_map;

int main (){
    try{

        // ----------------------------------------------------
        //  CARGA DE METADATOS
        // ----------------------------------------------------

        metadata_map = LoadColliderMetadata("metadata/colliders.json"); 
        
        if (metadata_map.empty()) {
            std::cerr << "ADVERTENCIA: No se pudieron cargar metadatos de colisión o el archivo está vacío. Las colisiones podrían fallar." << std::endl;
        }

        // ----------------------------------------------------
        //  INICIALIZADOR DE MANAGERS
        // ----------------------------------------------------

        ECS::Keyboard_t keyboard;
        ECS::EntityManager_t EntityMan;
        ECS::ResourceManager_t ResourceMan;

        // ----------------------------------------------------
        //  INICIALIZADOR DE SISTEMAS
        // ----------------------------------------------------
        
        RenderSystem_t<ECS::EntityManager_t> Render{ kSCRWIDTH, kSCRHEIGHT};
        PhysicsSystem_t<ECS::EntityManager_t> Physics;
        MovementSystem_t<ECS::EntityManager_t> Movement; 
        CollisionSystem_t<ECS::EntityManager_t> Collision{ kSCRWIDTH, kSCRHEIGHT };
        InputSystem_t<ECS::EntityManager_t> Input(keyboard);
        SpawnerSystem_t<ECS::EntityManager_t> Spawn;

        // ----------------------------------------------------
        //  INICIALIZADOR DE FABRICAS
        // ----------------------------------------------------

        GameObjectFactory_t GOFactory { EntityMan, ResourceMan};
        GOFactory.createPlayer(50, 200);
        GOFactory.createSpawner(200, 1,
            [&](const SpawnerComponent_t& sp){ //funcion lambda (explorar mas tarde)
                const auto* esp = EntityMan.getEntityByID( sp.getEntityID() );
                if(!esp) return;
                const auto* phy = esp->getComponent<PhysicsComponent_t>();
                if (!phy) return;
                auto& entity = GOFactory.createPlayer(phy->posX, phy->posY);
                std::cout << "Test Lambda \n";
        }); 

        // ----------------------------------------------------
        //  BUCLE PRINCIPAL DE JUEGO
        // ----------------------------------------------------

        while (Render.update( EntityMan )) {
            float delta = GetFrameTime();
            Input.update( EntityMan);
            Physics.update ( EntityMan, delta);
            Movement.update ( EntityMan, delta);
            Collision.update ( EntityMan );
            Spawn.update ( EntityMan );
        }
    }catch(...){
        std::cout << "Capturada : \n";
    }
    return 0;

}