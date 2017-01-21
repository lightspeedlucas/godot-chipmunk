## Chipmunk 2D integration module for Godot Engine

A simple C++ module integrating the Chipmunk 2D physics library into Godot Engine. **Development is still in very early stages, everything is untested.**

- Godot: https://godotengine.org
- Chipmunk 2D: http://chipmunk-physics.net

### Why?

Godot Engine already contains a very good, albeit simple, 2D physics engine implementation. It's based on Chipmunk and, for most games, is more than enough. However, 2D games that require a bit more control and flexibility over its physics could benefit from a bigger and more complex implementation.

### Features

- Integrates Chipmunk2D 7.0.1 into Godot as a C++ module.
- No setup required. If you can build Godot from source, you can use this module.
- Does not disable or replace Godot's 2D physics engine.
- Provides easy-to-use Object wrappers for every Chipmunk entity
  - i.e. `cpSpaceNew()` becomes `ChipmunkSpace.new()`
- Full access from C++ and GDScript
- ~~Offers Chipmunk functionality through custom Nodes, i.e. `ChipmunkRigidBody`~~ (Not yet implemented)

### Compilation

- Clone the contents of this repository into `<Your Godot source folder>/modules/chipmunk`
  - Please note that this project is meant to be used with Godot's **2.1** branch.
- Build and run Godot normally

### License

Released under the [MIT License](LICENSE).

### To Do

As this module is currently in its early stages of development, a lot is missing. `cpSpace`, `cpBody` and `cpShape` are almost completely wrapped (with GDScript bindings), only missing some stuff related to queries and callbacks. Nothing constraint-related is implemented right now.
