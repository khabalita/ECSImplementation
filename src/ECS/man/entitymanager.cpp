#include <ECS/man/entitymanager.hpp>
#include <algorithm>

namespace ECS {
    
EntityManager_t::EntityManager_t(){ m_Entity.reserve(NumInitialEntities);}

// Versión const
const Entity_t* EntityManager_t::getEntityByID(EntityID_t eid) const {
    auto it = std::find_if(m_Entity.begin(), m_Entity.end(),
        [&](const Entity_t& e){ return e.getEntityID() == eid; 
        });
    if (it == m_Entity.end())
        return nullptr;

    return &(*it);
}

// Versión no const
Entity_t* EntityManager_t::getEntityByID(EntityID_t eid) {
    // reutiliza la versión const
    auto ptr = static_cast<const EntityManager_t*>(this)->getEntityByID(eid);
    return const_cast<Entity_t*>(ptr);
}

} //namespace ECS

