#pragma once
#include <cstdint>
#include <chrono>
#include <functional>
#include <ECS/cmp/component.hpp>

using namespace std::chrono_literals; // cambiar esto

struct SpawnerComponent_t : public ECS::ComponentBase_t<SpawnerComponent_t> {
    using clk = std::chrono::steady_clock; // declaracion de un alias clk
    using PFunc_t = void (*)(void);

    explicit SpawnerComponent_t(ECS::EntityID_t eid)
        : ComponentBase_t(eid)
    {};
    std::function<void(SpawnerComponent_t&)> spawnMethod {}; //revisar mas tarde que hace function
    clk::time_point last_spawn_time { clk::now() }; // ultimo tiempo de spawn, lo inicio en now()
    std::chrono::duration<double> spawn_interval { 5s }; // intervalo de 5s (literals)
    std::size_t to_be_spawned { 2 }; // cantidad de spawns
};

