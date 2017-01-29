
#include <godot_chipmunk.h>
#include "chipmunk_damped_spring.h"

ChipmunkDampedSpring::ChipmunkDampedSpring(cpConstraint *constraint)
    : ChipmunkConstraint(constraint)
{
    ERR_FAIL_COND(!cpConstraintIsDampedSpring(constraint));
}

Vector2 ChipmunkDampedSpring::get_anchor_a() const
{
    return GD(cpDampedSpringGetAnchorA(constraint));
}

void ChipmunkDampedSpring::set_anchor_a(const Vector2 &value)
{
    cpDampedSpringSetAnchorA(constraint, CP(value));
}

Vector2 ChipmunkDampedSpring::get_anchor_b() const
{
    return GD(cpDampedSpringGetAnchorB(constraint));
}

void ChipmunkDampedSpring::set_anchor_b(const Vector2 &value)
{
    cpDampedSpringSetAnchorB(constraint, CP(value));
}

float ChipmunkDampedSpring::get_rest_length() const
{
    return cpDampedSpringGetRestLength(constraint);
}

void ChipmunkDampedSpring::set_rest_length(float value)
{
    cpDampedSpringSetRestLength(constraint, value);
}

float ChipmunkDampedSpring::get_stiffness() const
{
    return cpDampedSpringGetStiffness(constraint);
}

void ChipmunkDampedSpring::set_stiffness(float value)
{
    cpDampedSpringSetStiffness(constraint, value);
}

float ChipmunkDampedSpring::get_damping() const
{
    return cpDampedSpringGetDamping(constraint);
}

void ChipmunkDampedSpring::set_damping(float value)
{
    cpDampedSpringSetDamping(constraint, value);
}

void ChipmunkDampedSpring::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("get_anchor_a"), &ChipmunkDampedSpring::get_anchor_a);
    ObjectTypeDB::bind_method(_MD("set_anchor_a", "anchor:Vector2"), &ChipmunkDampedSpring::set_anchor_a);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "anchor_a"), _SCS("set_anchor_a"), _SCS("get_anchor_a"));

    ObjectTypeDB::bind_method(_MD("get_anchor_b"), &ChipmunkDampedSpring::get_anchor_b);
    ObjectTypeDB::bind_method(_MD("set_anchor_b", "anchor:Vector2"), &ChipmunkDampedSpring::set_anchor_b);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "anchor_b"), _SCS("set_anchor_b"), _SCS("get_anchor_b"));

    ObjectTypeDB::bind_method(_MD("get_rest_length"), &ChipmunkDampedSpring::get_rest_length);
    ObjectTypeDB::bind_method(_MD("set_rest_length", "length:real"), &ChipmunkDampedSpring::set_rest_length);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "rest_length"), _SCS("set_rest_length"), _SCS("get_rest_length"));

    ObjectTypeDB::bind_method(_MD("get_stiffness"), &ChipmunkDampedSpring::get_stiffness);
    ObjectTypeDB::bind_method(_MD("set_stiffness", "stiffness:real"), &ChipmunkDampedSpring::set_stiffness);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "stiffness"), _SCS("set_stiffness"), _SCS("get_stiffness"));

    ObjectTypeDB::bind_method(_MD("get_damping"), &ChipmunkDampedSpring::get_damping);
    ObjectTypeDB::bind_method(_MD("set_damping", "damping:real"), &ChipmunkDampedSpring::set_damping);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "damping"), _SCS("set_damping"), _SCS("get_damping"));
}

ChipmunkDampedSpring *ChipmunkConstraintFactory::damped_spring(ChipmunkBody *body_a, ChipmunkBody *body_b, const Vector2 &anchor_a, const Vector2 &anchor_b)
{
    ERR_FAIL_NULL_V(body_a, NULL);
    ERR_FAIL_NULL_V(body_b, NULL);
    auto *constraint = cpDampedSpringNew(*body_a, *body_b, CP(anchor_a), CP(anchor_b), 0, 0, 0);
    return memnew(ChipmunkDampedSpring(constraint));
}
