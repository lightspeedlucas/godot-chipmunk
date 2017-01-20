
#include "chipmunk_body.h"
#include "chipmunk_space.h"

ChipmunkBody::ChipmunkBody()
    : position_cb(0)
{
    body = cpBodyNew(0, 0);
    cpBodySetUserData(body, get_instance_ID());
}

ChipmunkBody::~ChipmunkBody()
{
    memdelete_notnull(position_cb);
    cpBodyFree(body);
}

void ChipmunkBody::activate()
{
    cpBodyActivate(body);
}

void ChipmunkBody::sleep()
{
    cpBodySleep(body);
}

bool ChipmunkBody::is_sleeping() const
{
    return cpBodyIsSleeping(body);
}

int ChipmunkBody::get_body_type() const
{
    return cpBodyGetType(body);
}

void ChipmunkBody::set_body_type(int value)
{
    cpBodySetType(body, static_cast<cpBodyType>(value));
}

ChipmunkSpace *ChipmunkBody::get_space() const
{
    return ChipmunkSpace::get(cpBodyGetSpace(body));
}

Vector2 ChipmunkBody::get_position() const
{
    return GD(cpBodyGetPosition(body));
}

void ChipmunkBody::set_position(const Vector2 &value)
{
    cpBodySetPosition(body, CP(value));
}

float ChipmunkBody::get_angle() const
{
    return cpBodyGetAngle(body);
}

void ChipmunkBody::set_angle(float value)
{
    cpBodySetAngle(body, value);
}

void ChipmunkBody::set_position_update_callback(Object *receiver, const StringName &method)
{
    memdelete_notnull(position_cb);
    cpBodySetPositionUpdateFunc(body, cpBodyUpdatePosition);

    if (receiver)
    {
        position_cb = memnew(ChipmunkCallbackBinding);
        position_cb->id = receiver->get_instance_ID();
        position_cb->method = method;
        cpBodySetPositionUpdateFunc(body, PositionUpdateFunc);
    }
}

void ChipmunkBody::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("activate"), &ChipmunkBody::activate);
    ObjectTypeDB::bind_method(_MD("sleep"), &ChipmunkBody::sleep);
    ObjectTypeDB::bind_method(_MD("is_sleeping"), &ChipmunkBody::is_sleeping);

    ObjectTypeDB::bind_method(_MD("get_body_type"), &ChipmunkBody::get_body_type);
    ObjectTypeDB::bind_method(_MD("set_body_type", "type:CP_BODY_TYPE_*"), &ChipmunkBody::set_body_type);

    ObjectTypeDB::bind_method(_MD("get_space"), &ChipmunkBody::get_space);

    ObjectTypeDB::bind_method(_MD("get_position"), &ChipmunkBody::get_position);
    ObjectTypeDB::bind_method(_MD("set_position", "position:Vector2"), &ChipmunkBody::set_position);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "position"), _SCS("set_position"), _SCS("get_position"));

    ObjectTypeDB::bind_method(_MD("get_angle"), &ChipmunkBody::get_angle);
    ObjectTypeDB::bind_method(_MD("set_angle", "angle:real"), &ChipmunkBody::set_angle);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "angle"), _SCS("set_angle"), _SCS("get_angle"));

    ObjectTypeDB::bind_method(_MD("set_position_update_callback", "receiver:Object", "method:StringName"), &ChipmunkBody::set_position_update_callback);

    BIND_CONSTANT(CP_BODY_TYPE_DYNAMIC);
    BIND_CONSTANT(CP_BODY_TYPE_KINEMATIC);
    BIND_CONSTANT(CP_BODY_TYPE_STATIC);
}

void ChipmunkBody::PositionUpdateFunc(cpBody *body, cpFloat dt)
{
    cpBodyUpdatePosition(body, dt);
    auto *obj = ChipmunkBody::get(body);
    if (obj->position_cb)
        obj->position_cb->call(body);
}

ChipmunkBody *ChipmunkBody::get(cpBody *body)
{
    auto id = body ? cpBodyGetUserData(body) : 0;
    return (ChipmunkBody*)ObjectDB::get_instance(id);
}
