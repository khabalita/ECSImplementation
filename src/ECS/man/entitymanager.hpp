#pragma once
#include <ECS/util/typealiases.hpp>
#include <ECS/cmp/entity.hpp>
#include <ECS/man/resourcemanager.hpp>
#include <ECS/man/componentstorage.hpp>

namespace ECS {

struct EntityManager_t { 
    static constexpr std::size_t NumInitialEntities { 1000 }; //al tamaño del vector, le reservo una cantidad finita de entidades
    explicit EntityManager_t();


    Entity_t& createEntity(){
      return m_Entity.emplace_back();
    }

    //add component
    template <typename CMP_t>
    CMP_t& addComponent(Entity_t& e) {
        CMP_t* cmp_ptr { e.getComponent<CMP_t>() };
        if ( !cmp_ptr ) {
            auto& cmp = m_components.createComponent<CMP_t>(e.getEntityID());
            e.addComponent(cmp);
            cmp_ptr = &cmp;
        }
        return *cmp_ptr;
    }

    const Entity_t* getEntityByID(EntityID_t eid) const;
          Entity_t* getEntityByID(EntityID_t eid);

    template <typename CMP_t>
    const Vec_t<CMP_t>& getComponents() const { return m_components.getComponents<CMP_t>(); }

    template <typename CMP_t>
          Vec_t<CMP_t>& getComponents()       { return m_components.getComponents<CMP_t>(); }

    const Vec_t<Entity_t>& getEntities() const { return m_Entity; }
         Vec_t<Entity_t>& getEntities()        { return m_Entity; }
    /*
    const Vec_t<PhysicsComponent_t>& getPhysicsComponents() const { return m_Components.getComponents<PhysicsComponent_t>(); };
          Vec_t<PhysicsComponent_t>& getPhysicsComponents()       { return m_Components.getComponents<PhysicsComponent_t>(); };
    
    const Vec_t<RenderComponent_t>& getRenderComponents() const { return m_Components.getComponents<RenderComponent_t>(); };
          Vec_t<RenderComponent_t>& getRenderComponents()       { return m_Components.getComponents<RenderComponent_t>(); };
    */
    ResourceManager_t& getResourceManager() { return m_Resources; }
    
private:
    Vec_t<Entity_t> m_Entity {};
    ComponentStorage_t m_components { NumInitialEntities };
    ResourceManager_t m_Resources {};
};

} //namespace ECS
