#ifndef GODOT_CHIPMUNK_DAMPED_SPRING_H
#define GODOT_CHIPMUNK_DAMPED_SPRING_H

#include "chipmunk_constraint.h"

class ChipmunkDampedSpring : public ChipmunkConstraint
{
    OBJ_TYPE(ChipmunkDampedSpring, ChipmunkConstraint);
protected:
    /** Abstract class */
    ChipmunkDampedSpring(cpConstraint*);
    friend class ChipmunkConstraintFactory;

public:
    /** Chipmunk methods */
    Vector2 get_anchor_a() const;
    void set_anchor_a(const Vector2&);

    Vector2 get_anchor_b() const;
    void set_anchor_b(const Vector2&);

    float get_rest_length() const;
    void set_rest_length(float);

    float get_stiffness() const;
    void set_stiffness(float);

    float get_damping() const;
    void set_damping(float);

protected:
    /** Godot bindings */
	static void _bind_methods();
};

#endif
