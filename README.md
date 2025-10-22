ECS Proyect

first steps

2D game engine in C++, implementing Entity Component System (ECS) architecture, ​​and Data-Oriented Design (DOP)

c++ version 20

Raylib Library for render and input system
  -> https://www.raylib.com

Currently in development

Main features:
  - Entity management
    
  - Entity factory
    
  - Component storage
      - RenderComponent (width, height, sprite (raylib))
      - InputComponent  (keybord (raylib))
      - PhysicsComponent (position X, Y)
      - ColliderComponent
    
  - Resource management, currently Textures
    
  - Systems responsible for bringing components to life
      - RenderSystem
      - PhysicsSystem
      - MovementSystem
      - InputSystem
      - CollisionSystem

Changelog:

  21/10
  
  - created -> library "libboundingbox" to adjust sprite collisions
    
  - added -> Nlohmann library for handling JSON
  - added -> metadata files to parse JSON
    
  - fixed -> Sprite Texture loaded and unloaded correctly on ResourceManager
  - fixed -> InputSystem with keyboard
  - fixed -> GameObjectFactory using library "libboundingbox"
