#ifndef GODOT_CHIPMUNK_CONSTRAINT_H
#define GODOT_CHIPMUNK_CONSTRAINT_H

#include <object.h>

class ChipmunkConstraint : public Object
{
    OBJ_TYPE(ChipmunkConstraint, Object);
protected:
    /** Abstract class */
    ChipmunkConstraint(cpConstraint*);

public:
    /** Lifecycle */
    ~ChipmunkConstraint();

    /** Chipmunk methods */
    ChipmunkSpace *get_space() const;

    ChipmunkBody *get_body_a() const;
    ChipmunkBody *get_body_b() const;

    float get_max_force() const;
    void set_max_force(float);

    float get_error_bias() const;
    void set_error_bias(float);

    float get_max_bias() const;
    void set_max_bias(float);

    bool get_collide_bodies() const;
    void set_collide_bodies(bool);

    Variant get_metadata() const;
    void set_metadata(const Variant&);

    float get_impulse() const;

protected:
    /** Godot bindings */
	static void _bind_methods();
    cpConstraint *constraint;
    Variant metadata;

public:
    /** Chipmunk interoperability */
    operator cpConstraint*() const { return constraint; }
    static ChipmunkConstraint *get(const cpConstraint*);
};

class ChipmunkConstraintFactory : public Reference
{
    OBJ_TYPE(ChipmunkConstraintFactory, Reference);
public:
    /** Factory methods */
    class ChipmunkPinJoint *pin_joint(ChipmunkBody *body_a, ChipmunkBody *body_b, const Vector2 &anchor_a, const Vector2 &anchor_b);

protected:
    /** Godot bindings */
	static void _bind_methods();
};

#endif
