#pragma once
#include <cstdint>
#include <vector>
#include <ECS/util/typealiases.hpp>
#include <ECS/cmp/component.hpp>

namespace ECS {

struct Entity_t {
    explicit Entity_t() = default;
    //falta implementar un constructor con un sprite (RAYLIB)

    //add component
    template <typename CMP_t>
    void addComponent(CMP_t& cmp){
        auto type = cmp.getComponentTypeID();
        m_components[type] = &cmp;
    }

    //get component const
    template <typename CMP_t>
    const CMP_t* getComponent() const {
        auto type = CMP_t::getComponentTypeID();
        auto iterator = m_components.find(type);
        if (iterator != m_components.end()) {
            return static_cast<const CMP_t*>(iterator->second);
        }
        return nullptr;
    }

    template <typename CMP_t>
    CMP_t* getComponent() {
        auto& cmp = const_cast<const Entity_t*>(this)->getComponent<CMP_t>();
        return const_cast<CMP_t*>(cmp);
    }

    constexpr EntityID_t getEntityID() const noexcept { return entityID; }
// MAL
private:
    Hash_t<ComponentTypeID_t, Component_t*> m_components;
    EntityID_t entityID { ++nextID };
    inline static EntityID_t nextID { 0 };
};

} //namespace ECS