#include <Game/cmp/render.hpp>
#include <ECS/man/resourcemanager.hpp>

RenderComponent_t::RenderComponent_t(ECS::EntityID_t eid, ECS::ResourceManager_t& rm, std::string filename)
    :ComponentBase_t(eid), hasTexture(!filename.empty()),w(32),h(32), color(RED)
    {
    if(hasTexture){
        texture = &rm.getTexture(filename);
        w = texture->width;
        h = texture->height;
    }
};

