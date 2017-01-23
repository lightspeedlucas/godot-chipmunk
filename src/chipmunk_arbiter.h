#ifndef GODOT_CHIPMUNK_ARBITER_H
#define GODOT_CHIPMUNK_ARBITER_H

#include <reference.h>

class ChipmunkArbiter : public Reference
{
    OBJ_TYPE(ChipmunkArbiter, Reference);
public:
    /** Wrap Chipmunk data */
    ChipmunkArbiter(cpArbiter*);

    /** Chipmunk methods */
    float get_restitution() const;
    void set_restitution(float);

    float get_friction() const;
    void set_friction(float);

    Vector2 get_surface_velocity() const;
    void set_surface_velocity(const Vector2&);

    Vector2 get_total_impulse() const;
    float get_total_kinetic_energy() const;

    bool ignore();

    ChipmunkShape *get_shape_a() const;
    ChipmunkShape *get_shape_b() const;

    ChipmunkBody *get_body_a() const;
    ChipmunkBody *get_body_b() const;

    Dictionary get_contact_point_set() const;

    bool is_first_contact() const;
    bool is_removal() const;

protected:
    /** Godot bindings */
	static void _bind_methods();
    cpArbiter *arbiter;

public:
    /** Chipmunk interoperability */
    operator cpArbiter*() const { return arbiter; }
};

#endif
