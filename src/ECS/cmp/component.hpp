#pragma once
#include <cstdint>
#include <ECS/util/typealiases.hpp>

namespace ECS {

// todos los componentes van a heredar de esta clase para tener un tipo en comun (ID)
// Ademas todos los componentes van a tener un ID a su entidad, obligatorio
struct Component_t {
    //todos los commponentes tienen que llamar al constructor de component
    explicit Component_t(EntityID_t eid)
        : entityID { eid }
    {}

    constexpr EntityID_t getEntityID() const noexcept { return entityID; }

protected:
    // inline --> hace la declaracion y definicion de una sola vez
    inline static ComponentTypeID_t nextTypeID { 0 };

private:
    EntityID_t entityID { 0 };
};

template <typename TYPE>
struct ComponentBase_t : Component_t{
    explicit ComponentBase_t(EntityID_t eid)
        : Component_t(eid)
    {}

    static ComponentTypeID_t getComponentTypeID() noexcept {
        static ComponentTypeID_t typeID { ++nextTypeID};
        return typeID;
    }
};

} // namespace ECS
