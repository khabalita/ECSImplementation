#include <ECS/man/entitymanager.hpp>
#include <Game/cmp/physics.hpp>
#include <Game/cmp/render.hpp>
#include <algorithm>

namespace ECS {
EntityManager_t::EntityManager_t(){
    m_Entity.reserve(NumInitialEntities);
}

const
Entity_t*
EntityManager_t::getEntityByID(EntityID_t eid) const {
    auto iterator = std::find_if(m_Entity.begin(), m_Entity.end(),
        [&](const auto& e) {return e.getEntityID() == eid; } 
    );
    if( iterator == m_Entity.end()){
        return nullptr;
    }
    return iterator.base();
}


Entity_t&
EntityManager_t::createEntity(){
    return m_Entity.emplace_back();
};

//version const para devolver un puntero a entity, de solo lectura
const Entity_t*
EntityManager_t::getEntityByID(EntityID_t eid) const {
    // recorro las entidades desde el comienzo hasta el final
    auto iterator = std::find_if(m_Entity.begin(), m_Entity.end(),
            // el & me permite "capturar" el eid que esta afuera del lambda
            // y pasarlo por referencia para que exista de forma local
            [&](const Entity_t& e){ return e.entityID == eid; } // miro si coinciden los IDS
        );
    if (iterator == m_Entity.end())
        return nullptr;
    
    return &(*iterator);
}



} //namespace ECS

