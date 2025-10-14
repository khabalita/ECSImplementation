#pragma once
#include <vector>
#include <memory>
#include <Game/cmp/physics.hpp>
#include <Game/cmp/input.hpp>
#include <Game/cmp/render.hpp>
#include <ECS/util/typealiases.hpp>

//clase que se encarga de almacenar componentes
namespace ECS{

//objeto generico
struct ComponentVectorBase_t {
    //destructor virtual
    virtual ~ComponentVectorBase_t() = default;
};

//objeto especifico
template <typename CPM_t>
struct ComponentVector_t : ComponentVectorBase_t {
    Vec_t<CPM_t> components;
};
    
struct ComponentStorage_t {
    // el constructor tiene un parametro de inicio, lo que significa que
    // estoy reservando en el physicsComponent, el valor inicial
    // std::size_t es de vector
    explicit ComponentStorage_t(std::size_t initialsize) 
        : m_initialSize(initialsize)
    {}
    
    // eliminacion de funciones de copia o asignacion de objetos componentstorage
    // referencia a un valor constante
    ComponentStorage_t(const ComponentStorage_t&) = delete;
    // doble && significa referencia a un valor temporal (r values)
    ComponentStorage_t(ComponentStorage_t&&) = delete;
    ComponentStorage_t& operator=(const ComponentStorage_t&) = delete;
    ComponentStorage_t& operator=(ComponentStorage_t&&) = delete;

    // !-- TEMPLATE --!

    // Create Components
    template <typename CMP_t>
    CMP_t&
    createComponent(EntityID_t eid){
        auto& v= getComponents<CMP_t>();
        auto& cmp = v.emplace_back(eid);
        return cmp;
    }
    // En createComponentVector():
    template <typename CMP_t>
    Vec_t<CMP_t>& createComponentVector(){
        auto typeID = CMP_t::getComponentTypeID();
        auto v = std::make_unique<ComponentVector_t<CMP_t>>();
        v->components.reserve(m_initialSize);
    
        // Simplificación:
        Vec_t<CMP_t>& result = v->components; // Guarda la referencia al vector
        m_componentVectors[typeID] = std::move(v);
    
        return result; // Retorna la referencia guardada
    }
    
    // metodo no const
    template <typename CMP_t>
    Vec_t<CMP_t>& getComponents() {
        auto typeID = CMP_t::getComponentTypeID();
        auto it = m_componentVectors.find(typeID);

        if (it == m_componentVectors.end()) {
            return createComponentVector<CMP_t>();
        }

        auto* v = static_cast<ComponentVector_t<CMP_t>*>(it->second.get());
        return v->components;   
    }

    // metodo const
    template <typename CMP_t>
    const Vec_t<CMP_t>& getComponents() const {
        auto typeID = CMP_t::getComponentTypeID();
        auto iterator = m_componentVectors.find(typeID);
    
        if (iterator != m_componentVectors.end()) {
            // Obtenemos el puntero del unique_ptr y lo casteamos al tipo derivado const
            auto* v = static_cast<const ComponentVector_t<CMP_t>*>(iterator->second.get());
            return v->components; // Retorna la referencia const directamente
        } else {
            // En un método const, no se puede crear el vector. Lanzar excepción es la acción correcta.
            throw std::runtime_error("No se puede obtener componente const porque no existe y no se permite su creacion.");
        }
    }

private:
    Hash_t<ComponentTypeID_t, std::unique_ptr<ComponentVectorBase_t>> m_componentVectors;
    std::size_t m_initialSize { 100 };

};

} // namespace ECS
