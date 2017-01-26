#ifndef GODOT_CHIPMUNK_PIVOT_JOINT_H
#define GODOT_CHIPMUNK_PIVOT_JOINT_H

#include "chipmunk_constraint.h"

class ChipmunkPivotJoint : public ChipmunkConstraint
{
    OBJ_TYPE(ChipmunkPivotJoint, ChipmunkConstraint);
protected:
    /** Abstract class */
    ChipmunkPivotJoint(cpConstraint*);
    friend class ChipmunkConstraintFactory;

public:
    /** Chipmunk methods */
    Vector2 get_anchor_a() const;
    void set_anchor_a(const Vector2&);

    Vector2 get_anchor_b() const;
    void set_anchor_b(const Vector2&);

protected:
    /** Godot bindings */
	static void _bind_methods();
};

#endif
