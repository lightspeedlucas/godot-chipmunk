
#include "chipmunk_body.h"

ChipmunkBody::ChipmunkBody()
    : ChipmunkBody(0, 0)
{
}

ChipmunkBody::ChipmunkBody(float mass, float inertia)
    : position_cb(0)
{
    body = cpBodyNew(mass, inertia);
    cpBodySetUserData(body, reinterpret_cast<void*>(get_instance_ID()));
}

ChipmunkBody::~ChipmunkBody()
{
    memdelete_notnull(position_cb);
    cpBodyFree(body);
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
    ObjectTypeDB::bind_method(_MD("set_position_update_callback", "receiver:Object", "method:StringName"), &ChipmunkBody::set_position_update_callback);
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
    auto id = reinterpret_cast<ObjectID>(cpBodyGetUserData(body));
    return (ChipmunkBody*)ObjectDB::get_instance(id);
}
