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
      m_Entity.emplace_back();
      return m_Entity.back();
    }

    // version no const
    template <typename CMP_t>
    Entity_t* getEntityFromComponent(const CMP_t& cmp){
        return getEntityByID( cmp.getEntityID() );
    }

    // version const
    template <typename CMP_t>
    const Entity_t* getEntityFromComponent(const CMP_t& cmp) const {
        return getEntityByID( cmp.getEntityID() );
    }

    // version const
    template <typename CMP_t, typename ReqCMP_t>
    const ReqCMP_t* getRequiredComponent(const CMP_t& cmp) const {
        auto* e = getEntityFromComponent(cmp);
        if (e) {
            return e->template getComponent<ReqCMP_t>();
        }
        return nullptr;
    }

    // version no const
    template <typename CMP_t, typename ReqCMP_t>
    ReqCMP_t* getRequiredComponent(const CMP_t& cmp){
        const ReqCMP_t* reqCom = const_cast<const EntityManager_t*>(this)->getRequiredComponent<CMP_t, ReqCMP_t>(cmp);
        return const_cast<ReqCMP_t*>(reqCom);
    }

    //add component con uso de typename ARGS que permite el paso de 0 a N numeros de parametros
    template <typename CMP_t, typename... Args>
    CMP_t& addComponent(Entity_t& e, Args&&... args) {
        CMP_t* cmp_ptr { e.getComponent<CMP_t>() };
        if ( !cmp_ptr ) {
            auto& cmp = m_components.createComponent<CMP_t>(e.getEntityID(), std::forward<Args>(args)...);
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

    ResourceManager_t& getResourceManager() { return m_Resources; }
    
private:
    Vec_t<Entity_t> m_Entity {};
    ComponentStorage_t m_components { NumInitialEntities };
    ResourceManager_t m_Resources {};
};

} //namespace ECS
