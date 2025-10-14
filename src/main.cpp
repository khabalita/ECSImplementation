
#include <iostream>
#include <cstdint>
#include <ECS/man/entitymanager.hpp>
#include <Game/sys/render.tpp>
#include <Game/sys/collision.tpp>
#include <Game/sys/physics.tpp>
#include <Game/cmp/collider.hpp>
#include <raylib.h>

constexpr uint32_t kSCRWIDTH  { 640 };
constexpr uint32_t kSCRHEIGHT { 360 };

//crea una entidad
ECS::Entity_t&
createEntity(ECS::EntityManager_t& em, uint32_t x, uint32_t y, const std::string_view filename){
    auto& entity   = em.createEntity();
    auto& ren      = em.addComponent<RenderComponent_t>(entity);
    auto& phy      = em.addComponent<PhysicsComponent_t>(entity);
    auto& col      = em.addComponent<ColliderComponent_t>(entity);
    phy.posX = x; phy.posY = y;
    col.box.xLeft   = 0;
    col.box.xRight  = ren.w;
    col.box.yUp     = 0;
    col.box.yDown   = ren.h;
    return entity;
}

//crea una entidad especifica (player)
void
createPlayer(ECS::EntityManager_t em, uint32_t x, uint32_t y){
    auto& entity = createEntity(em, 200, 70, "");
    em.addComponent<RenderComponent_t>(entity);
}

int main (){
    try{

        //Systems
        const RenderSystem_t<ECS::EntityManager_t> Render{ kSCRWIDTH, kSCRHEIGHT};
        PhysicsSystem_t<ECS::EntityManager_t> Physics;
        CollisionSystem_t<ECS::EntityManager_t> Collision;

        //Entities
        ECS::EntityManager_t entityMan;

        //main
        while (Render.update( entityMan )) {
            Physics.update ( entityMan );
            Collision.update ( entityMan );
        }
    }catch(...){
        std::cout << "Capturada : \n";
    }
    return 0;

}