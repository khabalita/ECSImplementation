#include <Game/cmp/render.hpp>
#include <ECS/man/resourcemanager.hpp>

RenderComponent_t::RenderComponent_t(ECS::EntityID_t eid, ECS::ResourceManager_t& rm, std::string filename)
    :ComponentBase_t(eid), w(32), h(32), hasTexture(false), texture(nullptr), color(RED)
    {
    if(!filename.empty()){
        texture = &rm.getTexture(filename);
        if(texture && texture->id != 0){
            hasTexture = true;
            w = texture->width;
            h = texture->height;
        }
    }
    
};

