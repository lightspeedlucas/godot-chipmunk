#ifndef GODOT_CHIPMUNK_SPACE_H
#define GODOT_CHIPMUNK_SPACE_H

#include <hash_map.h>
#include <object.h>

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

    ChipmunkBody *get_static_body() const;

    float get_current_timestep() const;
    bool is_locked() const;

    ChipmunkCollisionHandler *add_default_collision_handler();
    ChipmunkCollisionHandler *add_collision_handler(int type_a, int type_b);
    ChipmunkCollisionHandler *add_wildcard_handler(int type);

    void add_body(ChipmunkBody*);
    void remove_body(ChipmunkBody*);
    bool contains_body(ChipmunkBody*) const;

    void add_shape(ChipmunkShape*);
    void remove_shape(ChipmunkShape*);
    bool contains_shape(ChipmunkShape*) const;

    void add_constraint(ChipmunkConstraint*);
    void remove_constraint(ChipmunkConstraint*);
    bool contains_constraint(ChipmunkConstraint*) const;

    Array point_query(const Vector2 &point, float maxDistance, const Ref<ChipmunkShapeFilter> &filter) const;
    Dictionary point_query_nearest(const Vector2 &point, float maxDistance, const Ref<ChipmunkShapeFilter> &filter) const;

    Array segment_query(const Vector2 &start, const Vector2 &end, float radius, const Ref<ChipmunkShapeFilter> &filter) const;
    Dictionary segment_query_first(const Vector2 &start, const Vector2 &end, float radius, const Ref<ChipmunkShapeFilter> &filter) const;

    Array bb_query(const Rect2 &bb, const Ref<ChipmunkShapeFilter> &filter) const;

    Array shape_query(ChipmunkShape *shape) const;

    Array get_bodies() const;
    Array get_shapes() const;
    Array get_constraints() const;

    void step(float dt);

protected:
    /** Godot bindings */
	static void _bind_methods();
    cpSpace *space;
    ChipmunkBody *static_body;
    Variant metadata;

    /** Active collision handlers */
    friend class ChipmunkCollisionHandler;
    HashMap<uint32_t, ChipmunkCollisionHandler*> collision_handlers;
    uint32_t last_collision_handler_id;

public:
    /** Chipmunk interoperability */
    operator cpSpace*() const { return space; }
    static ChipmunkSpace *get(const cpSpace*);
};

#endif
