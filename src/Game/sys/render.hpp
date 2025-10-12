#pragma once
#include <cstdint>
#include <memory>
#include <util/typealiases.hpp>

struct EntityManager_t;
struct RenderComponent_t;
struct PhysicsComponent_t;

template <typename GameCTX_t>
struct RenderSystem_t {
    explicit RenderSystem_t(uint32_t width, uint32_t height);
    ~RenderSystem_t();

    bool update(const GameCTX_t& g) const;
    void beginFrame() const;
    void endFrame() const;
    void drawAllEntities(const GameCTX_t& g) const;
    void drawEntity(const RenderComponent_t& ren, const PhysicsComponent_t& phy) const;

private:
    uint32_t m_width;
    uint32_t m_height;
};