#include <Game/sys/spawn.hpp>
#include <Game/cmp/spawner.hpp>

template <typename GameCTX_t>
void
SpawnerSystem_t<GameCTX_t>::update(GameCTX_t& g) const {
    using clk = std::chrono::steady_clock;

    auto now = clk::now();
    for ( auto& spw: g.template getComponents<SpawnerComponent_t>() ) {
        auto* phy = g.template getRequiredComponent<SpawnerComponent_t, PhysicsComponent_t>(spw);
        if(phy) continue;

        auto passed { now - spw.last_spawn_time }; 
        if ( spw.to_be_spawned > 0 && passed > spw.spawn_interval ) {
            spw.spawnMethod(spw);
            spw.last_spawn_time = now;
            --spw.to_be_spawned;
        }
    }
}