#include <ECS/man/entitymanager.hpp>
#include <Game/sys/render.hpp>
#include <Game/sys/physics.hpp>
#include <raylib.h>

//Constructor
template <typename GameCTX_t>
RenderSystem_t<GameCTX_t>::RenderSystem_t(uint32_t width, uint32_t height)
    :m_width(width), m_height(height)
{
    InitWindow(width, height, "window");
    SetTargetFPS(60);
}

//Destructor
template <typename GameCTX_t>
RenderSystem_t<GameCTX_t>::~RenderSystem_t(){
    CloseWindow();
}
template <typename GameCTX_t>
bool 
RenderSystem_t<GameCTX_t>::update(const GameCTX_t& g) const {
    beginFrame();
    drawAllEntities(g);
    endFrame();
    return !WindowShouldClose();
}

template <typename GameCTX_t>
void
RenderSystem_t<GameCTX_t>::beginFrame() const {
    BeginDrawing();
    ClearBackground(WHITE);
}

template <typename GameCTX_t>
void
RenderSystem_t<GameCTX_t>::endFrame() const {
    EndDrawing();
}

template <typename GameCTX_t>
void
RenderSystem_t<GameCTX_t>::drawAllEntities(const GameCTX_t& g) const {
    for (const auto& entity : g.getEntities()) {

        const auto* phy = entity.template getComponent<PhysicsComponent_t>();
        const auto* ren = entity.template getComponent<RenderComponent_t>();

        if (phy && ren) {
            drawEntity(*ren, *phy);
        }
    }
}

template <typename GameCTX_t>
void
RenderSystem_t<GameCTX_t>::drawEntity( const RenderComponent_t& ren, const PhysicsComponent_t& phy) const {
    if (ren.hasTexture && ren.texture) {
        DrawTextureEx(
            *ren.texture,
            { static_cast<float>(phy.posX), static_cast<float>(phy.posY) },
            0.0f,
            1.0f,
            WHITE
        );
    } else {
        DrawRectangle(
            static_cast<int>(phy.posX),
            static_cast<int>(phy.posY),
            static_cast<int>(ren.w),
            static_cast<int>(ren.h),
            ren.color
        );
    }
}