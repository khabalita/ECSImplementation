#include <iostream>
#include <cstdint>
#include <ECS/man/entitymanager.hpp>
#include <Game/sys/render.tpp>
#include <Game/sys/collision.tpp>
#include <Game/sys/input.tpp>
#include <Game/sys/spawn.tpp>
#include <Game/sys/physics.tpp>
#include <Game/cmp/collider.hpp>
#include <Game/util/gameobjectfactory.hpp>
#include <raylib.h>

constexpr uint32_t kSCRWIDTH  { 640 };
constexpr uint32_t kSCRHEIGHT { 360 };

int main (){
    try{

        //Systems
        RenderSystem_t<ECS::EntityManager_t> Render{ kSCRWIDTH, kSCRHEIGHT};
        PhysicsSystem_t<ECS::EntityManager_t> Physics;
        CollisionSystem_t<ECS::EntityManager_t> Collision{ kSCRWIDTH, kSCRHEIGHT };
        // !REVISAR INPUT!
        InputSystem_t<ECS::EntityManager_t> Input (ECS::Keyboard_t kb);
        SpawnerSystem_t<ECS::EntityManager_t> Spawn;

        //Entities
        ECS::EntityManager_t EntityMan;
        ECS::ResourceManager_t ResourceMan;
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

        //main
        while (Render.update( EntityMan )) {
            Physics.update ( EntityMan );
            Collision.update ( EntityMan );
            Spawn.update ( EntityMan );
        }
    }catch(...){
        std::cout << "Capturada : \n";
    }
    return 0;

}