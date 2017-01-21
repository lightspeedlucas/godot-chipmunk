#ifndef GODOT_CHIPMUNK_PIN_JOINT_H
#define GODOT_CHIPMUNK_PIN_JOINT_H

#include "chipmunk_constraint.h"

class ChipmunkPinJoint : public ChipmunkConstraint
{
    OBJ_TYPE(ChipmunkPinJoint, ChipmunkConstraint);
protected:
    /** Abstract class */
    ChipmunkPinJoint(cpConstraint*);
    friend class ChipmunkConstraintFactory;

public:
    /** Chipmunk methods */
    Vector2 get_anchor_a() const;
    void set_anchor_a(const Vector2&);

    Vector2 get_anchor_b() const;
    void set_anchor_b(const Vector2&);

    float get_dist() const;
    void set_dist(float);

protected:
    /** Godot bindings */
	static void _bind_methods();
};

#endif
