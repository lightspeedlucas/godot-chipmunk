
#include <godot_chipmunk.h>
#include "chipmunk_pin_joint.h"

ChipmunkPinJoint::ChipmunkPinJoint(cpConstraint *constraint)
    : ChipmunkConstraint(constraint)
{
    ERR_FAIL_COND(!cpConstraintIsPinJoint(constraint));
}

Vector2 ChipmunkPinJoint::get_anchor_a() const
{
    return GD(cpPinJointGetAnchorA(constraint));
}

void ChipmunkPinJoint::set_anchor_a(const Vector2 &value)
{
    cpPinJointSetAnchorA(constraint, CP(value));
}

Vector2 ChipmunkPinJoint::get_anchor_b() const
{
    return GD(cpPinJointGetAnchorB(constraint));
}

void ChipmunkPinJoint::set_anchor_b(const Vector2 &value)
{
    cpPinJointSetAnchorB(constraint, CP(value));
}

float ChipmunkPinJoint::get_dist() const
{
    return cpPinJointGetDist(constraint);
}

void ChipmunkPinJoint::set_dist(float value)
{
    cpPinJointSetDist(constraint, value);
}

void ChipmunkPinJoint::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("get_anchor_a"), &ChipmunkPinJoint::get_anchor_a);
    ObjectTypeDB::bind_method(_MD("set_anchor_a", "anchor:Vector2"), &ChipmunkPinJoint::set_anchor_a);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "anchor_a"), _SCS("set_anchor_a"), _SCS("get_anchor_a"));

    ObjectTypeDB::bind_method(_MD("get_anchor_b"), &ChipmunkPinJoint::get_anchor_b);
    ObjectTypeDB::bind_method(_MD("set_anchor_b", "anchor:Vector2"), &ChipmunkPinJoint::set_anchor_b);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "anchor_b"), _SCS("set_anchor_b"), _SCS("get_anchor_b"));

    ObjectTypeDB::bind_method(_MD("get_dist"), &ChipmunkPinJoint::get_dist);
    ObjectTypeDB::bind_method(_MD("set_dist", "dist:real"), &ChipmunkPinJoint::set_dist);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "dist"), _SCS("set_dist"), _SCS("get_dist"));
}

ChipmunkPinJoint *ChipmunkConstraintFactory::pin_joint(ChipmunkBody *body_a, ChipmunkBody *body_b, const Vector2 &anchor_a, const Vector2 &anchor_b)
{
    auto *constraint = cpPinJointNew(*body_a, body_b ? (cpBody*)*body_b : 0, CP(anchor_a), CP(anchor_b));
    return memnew(ChipmunkPinJoint(constraint));
}
