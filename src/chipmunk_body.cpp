
#include <godot_chipmunk.h>
#include "chipmunk_body.h"

ChipmunkBody::ChipmunkBody()
    : position_cb(0), velocity_cb(0)
{
    body = cpBodyNew(0, 0);
    cpBodySetUserData(body, get_instance_ID());
}

ChipmunkBody::~ChipmunkBody()
{
    memdelete_notnull(position_cb);
    memdelete_notnull(velocity_cb);
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

float ChipmunkBody::get_mass() const
{
    return cpBodyGetMass(body);
}

void ChipmunkBody::set_mass(float value)
{
    cpBodySetMass(body, value);
}

float ChipmunkBody::get_moment() const
{
    return cpBodyGetMoment(body);
}

void ChipmunkBody::set_moment(float value)
{
    cpBodySetMoment(body, value);
}

void ChipmunkBody::set_moment_to_infinity()
{
    cpBodySetMoment(body, INFINITY);
}

Vector2 ChipmunkBody::get_position() const
{
    return GD(cpBodyGetPosition(body));
}

void ChipmunkBody::set_position(const Vector2 &value)
{
    cpBodySetPosition(body, CP(value));
}

Vector2 ChipmunkBody::get_center_of_gravity() const
{
    return GD(cpBodyGetCenterOfGravity(body));
}

void ChipmunkBody::set_center_of_gravity(const Vector2 &value)
{
    cpBodySetCenterOfGravity(body, CP(value));
}

Vector2 ChipmunkBody::get_velocity() const
{
    return GD(cpBodyGetVelocity(body));
}

void ChipmunkBody::set_velocity(const Vector2 &value)
{
    cpBodySetVelocity(body, CP(value));
}

Vector2 ChipmunkBody::get_force() const
{
    return GD(cpBodyGetForce(body));
}

void ChipmunkBody::set_force(const Vector2 &value)
{
    cpBodySetForce(body, CP(value));
}

float ChipmunkBody::get_angle() const
{
    return cpBodyGetAngle(body);
}

void ChipmunkBody::set_angle(float value)
{
    cpBodySetAngle(body, value);
}

float ChipmunkBody::get_angular_velocity() const
{
    return cpBodyGetAngularVelocity(body);
}

void ChipmunkBody::set_angular_velocity(float value)
{
    cpBodySetAngularVelocity(body, value);
}

float ChipmunkBody::get_torque() const
{
    return cpBodyGetTorque(body);
}

void ChipmunkBody::set_torque(float value)
{
    cpBodySetTorque(body, value);
}

Variant ChipmunkBody::get_metadata() const
{
    return metadata;
}

void ChipmunkBody::set_metadata(const Variant &value)
{
    metadata = value;
}

void ChipmunkBody::set_velocity_update_callback(Object *receiver, const StringName &method)
{
    memdelete_notnull(velocity_cb);
    cpBodySetVelocityUpdateFunc(body, cpBodyUpdateVelocity);

    if (receiver)
    {
        velocity_cb = memnew(ChipmunkCallbackBinding);
        velocity_cb->id = receiver->get_instance_ID();
        velocity_cb->method = method;
        cpBodySetVelocityUpdateFunc(body, VelocityUpdateFunc);
    }
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

void ChipmunkBody::apply_force_at_world_point(const Vector2 &force, const Vector2 &point)
{
    cpBodyApplyForceAtWorldPoint(body, CP(force), CP(point));
}

void ChipmunkBody::apply_force_at_local_point(const Vector2 &force, const Vector2 &point)
{
    cpBodyApplyForceAtLocalPoint(body, CP(force), CP(point));
}

void ChipmunkBody::apply_impulse_at_world_point(const Vector2 &impulse, const Vector2 &point)
{
    cpBodyApplyImpulseAtWorldPoint(body, CP(impulse), CP(point));
}

void ChipmunkBody::apply_impulse_at_local_point(const Vector2 &impulse, const Vector2 &point)
{
    cpBodyApplyImpulseAtLocalPoint(body, CP(impulse), CP(point));
}

Vector2 ChipmunkBody::get_velocity_at_world_point(const Vector2 &point)
{
    return GD(cpBodyGetVelocityAtWorldPoint(body, CP(point)));
}

Vector2 ChipmunkBody::get_velocity_at_local_point(const Vector2 &point)
{
    return GD(cpBodyGetVelocityAtLocalPoint(body, CP(point)));
}

float ChipmunkBody::get_kinetic_energy() const
{
    return cpBodyKineticEnergy(body);
}

Array ChipmunkBody::get_shapes() const
{
    struct Local
    {
        static void cb(cpBody *body, cpShape *shape, void *user_data)
        {
            auto *obj = ChipmunkShape::get(shape);
            ((Array*)user_data)->push_back(obj);
        }
    };

    Array r;
    cpBodyEachShape(body, &Local::cb, &r);
    return r;
}

Array ChipmunkBody::get_constraints() const
{
    struct Local
    {
        static void cb(cpBody *body, cpConstraint *constraint, void *user_data)
        {
            auto *obj = ChipmunkConstraint::get(constraint);
            ((Array*)user_data)->push_back(obj);
        }
    };

    Array r;
    cpBodyEachConstraint(body, &Local::cb, &r);
    return r;
}

Array ChipmunkBody::get_arbiters() const
{
    struct Local
    {
        static void cb(cpBody *body, cpArbiter *arbiter, void *user_data)
        {
            Ref<ChipmunkArbiter> ref = memnew(ChipmunkArbiter(arbiter));
            ((Array*)user_data)->push_back(ref);
        }
    };

    Array r;
    cpBodyEachArbiter(body, &Local::cb, &r);
    return r;
}

void ChipmunkBody::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("activate"), &ChipmunkBody::activate);
    ObjectTypeDB::bind_method(_MD("sleep"), &ChipmunkBody::sleep);
    ObjectTypeDB::bind_method(_MD("is_sleeping"), &ChipmunkBody::is_sleeping);

    ObjectTypeDB::bind_method(_MD("get_body_type"), &ChipmunkBody::get_body_type);
    ObjectTypeDB::bind_method(_MD("set_body_type", "type:int"), &ChipmunkBody::set_body_type);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "body_type"), _SCS("set_body_type"), _SCS("get_body_type"));

    ObjectTypeDB::bind_method(_MD("get_space"), &ChipmunkBody::get_space);

    ObjectTypeDB::bind_method(_MD("get_mass"), &ChipmunkBody::get_mass);
    ObjectTypeDB::bind_method(_MD("set_mass", "mass:real"), &ChipmunkBody::set_mass);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "mass"), _SCS("set_mass"), _SCS("get_mass"));

    ObjectTypeDB::bind_method(_MD("get_moment"), &ChipmunkBody::get_moment);
    ObjectTypeDB::bind_method(_MD("set_moment", "moment:real"), &ChipmunkBody::set_moment);
    ObjectTypeDB::bind_method(_MD("set_moment_to_infinity"), &ChipmunkBody::set_moment_to_infinity);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "moment"), _SCS("set_moment"), _SCS("get_moment"));

    ObjectTypeDB::bind_method(_MD("get_position"), &ChipmunkBody::get_position);
    ObjectTypeDB::bind_method(_MD("set_position", "position:Vector2"), &ChipmunkBody::set_position);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "position"), _SCS("set_position"), _SCS("get_position"));

    ObjectTypeDB::bind_method(_MD("get_center_of_gravity"), &ChipmunkBody::get_center_of_gravity);
    ObjectTypeDB::bind_method(_MD("set_center_of_gravity", "center_of_gravity:Vector2"), &ChipmunkBody::set_center_of_gravity);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "center_of_gravity"), _SCS("set_center_of_gravity"), _SCS("get_center_of_gravity"));

    ObjectTypeDB::bind_method(_MD("get_velocity"), &ChipmunkBody::get_velocity);
    ObjectTypeDB::bind_method(_MD("set_velocity", "velocity:Vector2"), &ChipmunkBody::set_velocity);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "velocity"), _SCS("set_velocity"), _SCS("get_velocity"));

    ObjectTypeDB::bind_method(_MD("get_force"), &ChipmunkBody::get_force);
    ObjectTypeDB::bind_method(_MD("set_force", "force:Vector2"), &ChipmunkBody::set_force);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "force"), _SCS("set_force"), _SCS("get_force"));

    ObjectTypeDB::bind_method(_MD("get_angle"), &ChipmunkBody::get_angle);
    ObjectTypeDB::bind_method(_MD("set_angle", "angle:real"), &ChipmunkBody::set_angle);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "angle"), _SCS("set_angle"), _SCS("get_angle"));

    ObjectTypeDB::bind_method(_MD("get_angular_velocity"), &ChipmunkBody::get_angular_velocity);
    ObjectTypeDB::bind_method(_MD("set_angular_velocity", "angular_velocity:real"), &ChipmunkBody::set_angular_velocity);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "angular_velocity"), _SCS("set_angular_velocity"), _SCS("get_angular_velocity"));

    ObjectTypeDB::bind_method(_MD("get_torque"), &ChipmunkBody::get_torque);
    ObjectTypeDB::bind_method(_MD("set_torque", "torque:real"), &ChipmunkBody::set_torque);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "torque"), _SCS("set_torque"), _SCS("get_torque"));

    ObjectTypeDB::bind_method(_MD("get_metadata"), &ChipmunkBody::get_metadata);
    ObjectTypeDB::bind_method(_MD("set_metadata", "metadata:Variant"), &ChipmunkBody::set_metadata);

    ObjectTypeDB::bind_method(_MD("set_velocity_update_callback", "receiver:Object", "method:StringName"), &ChipmunkBody::set_velocity_update_callback);
    ObjectTypeDB::bind_method(_MD("set_position_update_callback", "receiver:Object", "method:StringName"), &ChipmunkBody::set_position_update_callback);

    ObjectTypeDB::bind_method(_MD("apply_force_at_world_point", "force:Vector2", "point:Vector2"), &ChipmunkBody::apply_force_at_world_point);
    ObjectTypeDB::bind_method(_MD("apply_force_at_local_point", "force:Vector2", "point:Vector2"), &ChipmunkBody::apply_force_at_local_point);

    ObjectTypeDB::bind_method(_MD("apply_impulse_at_world_point", "impulse:Vector2", "point:Vector2"), &ChipmunkBody::apply_impulse_at_world_point);
    ObjectTypeDB::bind_method(_MD("apply_impulse_at_local_point", "impulse:Vector2", "point:Vector2"), &ChipmunkBody::apply_impulse_at_local_point);

    ObjectTypeDB::bind_method(_MD("get_velocity_at_world_point", "point:Vector2"), &ChipmunkBody::get_velocity_at_world_point);
    ObjectTypeDB::bind_method(_MD("get_velocity_at_local_point", "point:Vector2"), &ChipmunkBody::get_velocity_at_local_point);

    ObjectTypeDB::bind_method(_MD("get_kinetic_energy"), &ChipmunkBody::get_kinetic_energy);

    ObjectTypeDB::bind_method(_MD("get_shapes:Array"), &ChipmunkBody::get_shapes);
    ObjectTypeDB::bind_method(_MD("get_constraints:Array"), &ChipmunkBody::get_constraints);
    ObjectTypeDB::bind_method(_MD("get_arbiters:Array"), &ChipmunkBody::get_arbiters);

    ObjectTypeDB::bind_integer_constant(get_type_static(), "DYNAMIC", CP_BODY_TYPE_DYNAMIC);
    ObjectTypeDB::bind_integer_constant(get_type_static(), "KINEMATIC", CP_BODY_TYPE_KINEMATIC);
    ObjectTypeDB::bind_integer_constant(get_type_static(), "STATIC", CP_BODY_TYPE_STATIC);

    BIND_CONSTANT(CP_BODY_TYPE_DYNAMIC);
    BIND_CONSTANT(CP_BODY_TYPE_KINEMATIC);
    BIND_CONSTANT(CP_BODY_TYPE_STATIC);
}

void ChipmunkBody::VelocityUpdateFunc(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt)
{
    cpBodyUpdateVelocity(body, gravity, damping, dt);
    auto *obj = ChipmunkBody::get(body);
    if (obj->velocity_cb)
        obj->velocity_cb->call(obj);
}

void ChipmunkBody::PositionUpdateFunc(cpBody *body, cpFloat dt)
{
    cpBodyUpdatePosition(body, dt);
    auto *obj = ChipmunkBody::get(body);
    if (obj->position_cb)
        obj->position_cb->call(obj);
}

ChipmunkBody *ChipmunkBody::get(const cpBody *body)
{
    auto id = body ? cpBodyGetUserData(body) : 0;
    return (ChipmunkBody*)ObjectDB::get_instance(id);
}
