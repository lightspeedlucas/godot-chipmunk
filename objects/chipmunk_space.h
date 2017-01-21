#ifndef GODOT_CHIPMUNK_SPACE_H
#define GODOT_CHIPMUNK_SPACE_H

#include "object.h"
#include "chipmunk_common.h"

class ChipmunkSpace : public Object
{
    OBJ_TYPE(ChipmunkSpace, Object);
public:
    /** Lifecycle */
    ChipmunkSpace();
    ~ChipmunkSpace();

    /** Chipmunk methods */
    int get_iterations() const;
    void set_iterations(int);

    Vector2 get_gravity() const;
    void set_gravity(const Vector2&);

    float get_damping() const;
    void set_damping(float);

    float get_idle_speed_threshold() const;
    void set_idle_speed_threshold(float);

    float get_sleep_time_threshold() const;
    void set_sleep_time_threshold(float);

    float get_collision_slop() const;
    void set_collision_slop(float);

    float get_collision_bias() const;
    void set_collision_bias(float);

    int get_collision_persistence() const;
    void set_collision_persistence(int);

    Variant get_metadata() const;
    void set_metadata(const Variant&);
    
    float get_current_timestep() const;
    bool is_locked() const;

    void add_body(ChipmunkBody*);
    void remove_body(ChipmunkBody*);
    bool contains_body(ChipmunkBody*) const;

    void add_shape(ChipmunkShape*);
    void remove_shape(ChipmunkShape*);
    bool contains_shape(ChipmunkShape*) const;

    Array point_query(const Vector2 &point, float maxDistance, const Ref<ChipmunkShapeFilter> &filter) const;
    Dictionary point_query_nearest(const Vector2 &point, float maxDistance, const Ref<ChipmunkShapeFilter> &filter) const;

    void step(float dt);

protected:
    /** Godot bindings */
	static void _bind_methods();
    cpSpace *space;
    Variant metadata;

public:
    /** Chipmunk interoperability */
    operator cpSpace*() const { return space; }
    static ChipmunkSpace *get(const cpSpace*);
};

#endif
