
#include <godot_chipmunk.h>
#include "chipmunk_constraint.h"

ChipmunkConstraint::ChipmunkConstraint(cpConstraint *constraint)
    : constraint(constraint)
{
    cpConstraintSetUserData(constraint, get_instance_ID());
}

ChipmunkConstraint::~ChipmunkConstraint()
{
    cpConstraintFree(constraint);
}

ChipmunkSpace *ChipmunkConstraint::get_space() const
{
    return ChipmunkSpace::get(cpConstraintGetSpace(constraint));
}

ChipmunkBody *ChipmunkConstraint::get_body_a() const
{
    return ChipmunkBody::get(cpConstraintGetBodyA(constraint));
}

ChipmunkBody *ChipmunkConstraint::get_body_b() const
{
    return ChipmunkBody::get(cpConstraintGetBodyB(constraint));
}

float ChipmunkConstraint::get_max_force() const
{
    return cpConstraintGetMaxForce(constraint);
}

void ChipmunkConstraint::set_max_force(float value)
{
    cpConstraintSetMaxForce(constraint, value);
}

float ChipmunkConstraint::get_error_bias() const
{
    return cpConstraintGetErrorBias(constraint);
}

void ChipmunkConstraint::set_error_bias(float value)
{
    cpConstraintSetErrorBias(constraint, value);
}

float ChipmunkConstraint::get_max_bias() const
{
    return cpConstraintGetMaxBias(constraint);
}

void ChipmunkConstraint::set_max_bias(float value)
{
    cpConstraintSetMaxBias(constraint, value);
}

bool ChipmunkConstraint::get_collide_bodies() const
{
    return cpConstraintGetCollideBodies(constraint);
}

void ChipmunkConstraint::set_collide_bodies(bool value)
{
    cpConstraintSetCollideBodies(constraint, value);
}

Variant ChipmunkConstraint::get_metadata() const
{
    return metadata;
}

void ChipmunkConstraint::set_metadata(const Variant &value)
{
    metadata = value;
}

float ChipmunkConstraint::get_impulse() const
{
    return cpConstraintGetImpulse(constraint);
}

void ChipmunkConstraint::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("get_space"), &ChipmunkConstraint::get_space);

    ObjectTypeDB::bind_method(_MD("get_body_a"), &ChipmunkConstraint::get_body_a);
    ObjectTypeDB::bind_method(_MD("get_body_b"), &ChipmunkConstraint::get_body_b);

    ObjectTypeDB::bind_method(_MD("get_max_force"), &ChipmunkConstraint::get_max_force);
    ObjectTypeDB::bind_method(_MD("set_max_force", "force:real"), &ChipmunkConstraint::set_max_force);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "max_force"), _SCS("set_max_force"), _SCS("get_max_force"));

    ObjectTypeDB::bind_method(_MD("get_error_bias"), &ChipmunkConstraint::get_error_bias);
    ObjectTypeDB::bind_method(_MD("set_error_bias", "bias:real"), &ChipmunkConstraint::set_error_bias);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "error_bias"), _SCS("set_error_bias"), _SCS("get_error_bias"));

    ObjectTypeDB::bind_method(_MD("get_max_bias"), &ChipmunkConstraint::get_max_bias);
    ObjectTypeDB::bind_method(_MD("set_max_bias", "bias:real"), &ChipmunkConstraint::set_max_bias);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "max_bias"), _SCS("set_max_bias"), _SCS("get_max_bias"));

    ObjectTypeDB::bind_method(_MD("get_collide_bodies"), &ChipmunkConstraint::get_collide_bodies);
    ObjectTypeDB::bind_method(_MD("set_collide_bodies", "collide:bool"), &ChipmunkConstraint::set_collide_bodies);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "collide_bodies"), _SCS("set_collide_bodies"), _SCS("get_collide_bodies"));

    ObjectTypeDB::bind_method(_MD("get_metadata"), &ChipmunkConstraint::get_metadata);
    ObjectTypeDB::bind_method(_MD("set_metadata", "metadata:Variant"), &ChipmunkConstraint::set_metadata);

    ObjectTypeDB::bind_method(_MD("get_impulse"), &ChipmunkConstraint::get_impulse);
}

ChipmunkConstraint *ChipmunkConstraint::get(const cpConstraint *constraint)
{
    auto id = constraint ? cpConstraintGetUserData(constraint) : 0;
    return (ChipmunkConstraint*)ObjectDB::get_instance(id);
}

void ChipmunkConstraintFactory::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("pin_joint:ChipmunkPinJoint", "body_a:ChipmunkBody", "body_b:ChipmunkBody", "anchor_a:Vector2", "anchor_b:Vector2"), &ChipmunkConstraintFactory::pin_joint);
    ObjectTypeDB::bind_method(_MD("pivot_joint:ChipmunkPinJoint", "body_a:ChipmunkBody", "body_b:ChipmunkBody", "anchor_a:Vector2", "anchor_b:Vector2"), &ChipmunkConstraintFactory::pivot_joint);
}
