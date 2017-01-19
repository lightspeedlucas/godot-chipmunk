#ifndef GODOT_CHIPMUNK_SPACE_H
#define GODOT_CHIPMUNK_SPACE_H

#include "object.h"
#include "reference.h"

#include "chipmunk/chipmunk.h"

class ChipmunkBody;

class ChipmunkSpace : public Reference
{
    OBJ_TYPE(ChipmunkSpace, Reference);
public:
    ChipmunkSpace();

    void destroy();

    // int get_iterations() const;
    // void set_iterations(int);

    Vector2 get_gravity() const;
    void set_gravity(const Vector2&);

    // float get_damping() const;
    // void set_damping(float);

    // float get_idle_speed_threshold() const;
    // void set_idle_speed_threshold(float);

    // float get_sleep_time_threshold() const;
    // void set_sleep_time_threshold(float);

    // float get_collision_slop() const;
    // void set_collision_slop(float);

    // float get_collision_bias() const;
    // void set_collision_bias(float);

    // int get_collision_persistence() const;
    // void set_collision_persistence(int);

    // Variant get_metadata() const;
    // void set_metadata(const Variant&);

    // Ref<ChipmunkBody> get_static_body() const;
    
    // float get_current_timestep() const;
    // bool is_locked();

    void add_body(const Ref<ChipmunkBody>&);
    void remove_body(const Ref<ChipmunkBody>&);

protected:
	static void _bind_methods();

    cpSpace *space;

public:
    explicit ChipmunkSpace(cpSpace *space) : space(space) {}
    operator cpSpace*() const { return space; }
};

#endif
