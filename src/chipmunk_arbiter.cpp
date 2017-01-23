
#include <godot_chipmunk.h>
#include "chipmunk_arbiter.h"

ChipmunkArbiter::ChipmunkArbiter(cpArbiter *arbiter)
    : arbiter(arbiter)
{
}

float ChipmunkArbiter::get_restitution() const
{
    return cpArbiterGetRestitution(arbiter);
}

void ChipmunkArbiter::set_restitution(float value)
{
    cpArbiterSetRestitution(arbiter, value);
}

float ChipmunkArbiter::get_friction() const
{
    return cpArbiterGetFriction(arbiter);
}

void ChipmunkArbiter::set_friction(float value)
{
    cpArbiterSetFriction(arbiter, value);
}

Vector2 ChipmunkArbiter::get_surface_velocity() const
{
    return GD(cpArbiterGetSurfaceVelocity(arbiter));
}

void ChipmunkArbiter::set_surface_velocity(const Vector2 &value)
{
    cpArbiterSetSurfaceVelocity(arbiter, CP(value));
}

Vector2 ChipmunkArbiter::get_total_impulse() const
{
    return GD(cpArbiterTotalImpulse(arbiter));
}

float ChipmunkArbiter::get_total_kinetic_energy() const
{
    return cpArbiterTotalKE(arbiter);
}

bool ChipmunkArbiter::ignore()
{
    return cpArbiterIgnore(arbiter);
}

ChipmunkShape *ChipmunkArbiter::get_shape_a() const
{
    CP_ARBITER_GET_SHAPES(arbiter, a, b);
    return ChipmunkShape::get(a);
}

ChipmunkShape *ChipmunkArbiter::get_shape_b() const
{
    CP_ARBITER_GET_SHAPES(arbiter, a, b);
    return ChipmunkShape::get(b);
}

ChipmunkBody *ChipmunkArbiter::get_body_a() const
{
    CP_ARBITER_GET_BODIES(arbiter, a, b);
    return ChipmunkBody::get(a);
}

ChipmunkBody *ChipmunkArbiter::get_body_b() const
{
    CP_ARBITER_GET_BODIES(arbiter, a, b);
    return ChipmunkBody::get(b);
}

Dictionary ChipmunkArbiter::get_contact_point_set() const
{
    auto set = cpArbiterGetContactPointSet(arbiter);
    Dictionary r(true);
    r["count"] = set.count;
    r["normal"] = GD(set.normal);
    Array points;
    for (int i = 0; i < set.count; ++i)
    {
        Dictionary r(true);
        r["pointA"] = GD(set.points[i].pointA);
        r["pointB"] = GD(set.points[i].pointB);
        r["distance"] = set.points[i].distance;
        points.push_back(r);
    }
    r["points"] = points;
    return r;
}

bool ChipmunkArbiter::is_first_contact() const
{
    return cpArbiterIsFirstContact(arbiter);
}

bool ChipmunkArbiter::is_removal() const
{
    return cpArbiterIsRemoval(arbiter);
}

void ChipmunkArbiter::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("get_restitution:real"), &ChipmunkArbiter::get_restitution);
    ObjectTypeDB::bind_method(_MD("set_restitution", "restitution:real"), &ChipmunkArbiter::set_restitution);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "restitution"), _SCS("set_restitution"), _SCS("get_restitution"));

    ObjectTypeDB::bind_method(_MD("get_friction:real"), &ChipmunkArbiter::get_friction);
    ObjectTypeDB::bind_method(_MD("set_friction", "friction:real"), &ChipmunkArbiter::set_friction);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "friction"), _SCS("set_friction"), _SCS("get_friction"));

    ObjectTypeDB::bind_method(_MD("get_surface_velocity:Vector2"), &ChipmunkArbiter::get_surface_velocity);
    ObjectTypeDB::bind_method(_MD("set_surface_velocity", "velocity:Vector2"), &ChipmunkArbiter::set_surface_velocity);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "surface_velocity"), _SCS("set_surface_velocity"), _SCS("get_surface_velocity"));

    ObjectTypeDB::bind_method(_MD("get_total_impulse:Vector2"), &ChipmunkArbiter::get_total_impulse);
    ObjectTypeDB::bind_method(_MD("get_total_kinetic_energy:real"), &ChipmunkArbiter::get_total_kinetic_energy);

    ObjectTypeDB::bind_method(_MD("ignore:bool"), &ChipmunkArbiter::ignore);

    ObjectTypeDB::bind_method(_MD("get_shape_a:ChipmunkShape"), &ChipmunkArbiter::get_shape_a);
    ObjectTypeDB::bind_method(_MD("get_shape_b:ChipmunkShape"), &ChipmunkArbiter::get_shape_b);

    ObjectTypeDB::bind_method(_MD("get_body_a:ChipmunkBody"), &ChipmunkArbiter::get_body_a);
    ObjectTypeDB::bind_method(_MD("get_body_b:ChipmunkBody"), &ChipmunkArbiter::get_body_b);

    ObjectTypeDB::bind_method(_MD("get_contact_point_set:Dictionary"), &ChipmunkArbiter::get_contact_point_set);

    ObjectTypeDB::bind_method(_MD("is_first_contact:bool"), &ChipmunkArbiter::is_first_contact);
    ObjectTypeDB::bind_method(_MD("is_removal:bool"), &ChipmunkArbiter::is_removal);
}
