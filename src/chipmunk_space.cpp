
#include <godot_chipmunk.h>
#include "chipmunk_space.h"

ChipmunkSpace::ChipmunkSpace()
    : last_collision_handler_id(0)
{
    space = cpSpaceNew();
    cpSpaceSetUserData(space, get_instance_ID());
}

ChipmunkSpace::~ChipmunkSpace()
{
    List<uint32_t> keys;
	collision_handlers.get_key_list(&keys);

    for (auto *e = keys.front(); e; e = e->next())
        memdelete(collision_handlers[e->get()]);

    cpSpaceFree(space);
}

int ChipmunkSpace::get_iterations() const
{
    return cpSpaceGetIterations(space);
}

void ChipmunkSpace::set_iterations(int value)
{
    cpSpaceSetIterations(space, value);
}

Vector2 ChipmunkSpace::get_gravity() const
{
    return GD(cpSpaceGetGravity(space));
}

void ChipmunkSpace::set_gravity(const Vector2 &value)
{
    cpSpaceSetGravity(space, CP(value));
}

float ChipmunkSpace::get_damping() const
{
    return cpSpaceGetDamping(space);
}

void ChipmunkSpace::set_damping(float value)
{
    cpSpaceSetDamping(space, value);
}

float ChipmunkSpace::get_idle_speed_threshold() const
{
    return cpSpaceGetIdleSpeedThreshold(space);
}

void ChipmunkSpace::set_idle_speed_threshold(float value)
{
    cpSpaceSetIdleSpeedThreshold(space, value);
}

float ChipmunkSpace::get_sleep_time_threshold() const
{
    return cpSpaceGetSleepTimeThreshold(space);
}

void ChipmunkSpace::set_sleep_time_threshold(float value)
{
    cpSpaceSetSleepTimeThreshold(space, value);
}

float ChipmunkSpace::get_collision_slop() const
{
    return cpSpaceGetCollisionSlop(space);
}

void ChipmunkSpace::set_collision_slop(float value)
{
    cpSpaceSetCollisionSlop(space, value);
}

float ChipmunkSpace::get_collision_bias() const
{
    return cpSpaceGetCollisionBias(space);
}

void ChipmunkSpace::set_collision_bias(float value)
{
    cpSpaceSetCollisionBias(space, value);
}

int ChipmunkSpace::get_collision_persistence() const
{
    return cpSpaceGetCollisionPersistence(space);
}

void ChipmunkSpace::set_collision_persistence(int value)
{
    cpSpaceSetCollisionPersistence(space, value);
}

Variant ChipmunkSpace::get_metadata() const
{
    return metadata;
}

void ChipmunkSpace::set_metadata(const Variant &value)
{
    metadata = value;
}

float ChipmunkSpace::get_current_timestep() const
{
    return cpSpaceGetCurrentTimeStep(space);
}

bool ChipmunkSpace::is_locked() const
{
    return cpSpaceIsLocked(space);
}

ChipmunkCollisionHandler *ChipmunkSpace::add_default_collision_handler()
{
    auto *handler = cpSpaceAddDefaultCollisionHandler(space);
    return ChipmunkCollisionHandler::get_or_create(this, handler);
}

ChipmunkCollisionHandler *ChipmunkSpace::add_collision_handler(int type_a, int type_b)
{
    auto *handler = cpSpaceAddCollisionHandler(space, type_a, type_b);
    return ChipmunkCollisionHandler::get_or_create(this, handler);
}

ChipmunkCollisionHandler *ChipmunkSpace::add_wildcard_handler(int type)
{
    auto *handler = cpSpaceAddWildcardHandler(space, type);
    return ChipmunkCollisionHandler::get_or_create(this, handler);
}

void ChipmunkSpace::add_body(ChipmunkBody *body)
{
    ERR_FAIL_NULL(body);
    cpSpaceAddBody(space, *body);
}

void ChipmunkSpace::remove_body(ChipmunkBody *body)
{
    ERR_FAIL_NULL(body);
    cpSpaceRemoveBody(space, *body);
}

bool ChipmunkSpace::contains_body(ChipmunkBody *body) const
{
    ERR_FAIL_NULL_V(body, false);
    return cpSpaceContainsBody(space, *body);
}

void ChipmunkSpace::add_shape(ChipmunkShape *shape)
{
    ERR_FAIL_NULL(shape);
    cpSpaceAddShape(space, *shape);
}

void ChipmunkSpace::remove_shape(ChipmunkShape *shape)
{
    ERR_FAIL_NULL(shape);
    cpSpaceRemoveShape(space, *shape);
}

bool ChipmunkSpace::contains_shape(ChipmunkShape *shape) const
{
    ERR_FAIL_NULL_V(shape, false);
    return cpSpaceContainsShape(space, *shape);
}

void ChipmunkSpace::add_constraint(ChipmunkConstraint *constraint)
{
    ERR_FAIL_NULL(constraint);
    cpSpaceAddConstraint(space, *constraint);
}

void ChipmunkSpace::remove_constraint(ChipmunkConstraint *constraint)
{
    ERR_FAIL_NULL(constraint);
    cpSpaceRemoveConstraint(space, *constraint);
}

bool ChipmunkSpace::contains_constraint(ChipmunkConstraint *constraint) const
{
    ERR_FAIL_NULL_V(constraint, false);
    return cpSpaceContainsConstraint(space, *constraint);
}

Array ChipmunkSpace::point_query(const Vector2 &point, float maxDistance, const Ref<ChipmunkShapeFilter> &filter) const
{
    struct Local
    {
        static void cb(cpShape *shape, cpVect point, cpFloat distance, cpVect gradient, void *user_data)
        {
            Dictionary r(true);
            r["shape"] = ChipmunkShape::get(shape);
            r["point"] = GD(point);
            r["distance"] = distance;
            r["gradient"] = GD(gradient);
            ((Array*)user_data)->push_back(r);
        }
    };

    Array r;
    cpSpacePointQuery(space, CP(point), maxDistance, **filter, &Local::cb, &r);
    return r;
}

Dictionary ChipmunkSpace::point_query_nearest(const Vector2 &point, float maxDistance, const Ref<ChipmunkShapeFilter> &filter) const
{
    cpPointQueryInfo info;
    Dictionary r(true);
    if (cpSpacePointQueryNearest(space, CP(point), maxDistance, **filter, &info))
    {
        r["shape"] = ChipmunkShape::get(info.shape);
        r["point"] = GD(info.point);
        r["distance"] = info.distance;
        r["gradient"] = GD(info.gradient);
    }
    return r;
}

void ChipmunkSpace::step(float dt)
{
    cpSpaceStep(space, dt);
}

void ChipmunkSpace::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("get_iterations"), &ChipmunkSpace::get_iterations);
    ObjectTypeDB::bind_method(_MD("set_iterations", "iterations:int"), &ChipmunkSpace::set_iterations);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "iterations"), _SCS("set_iterations"), _SCS("get_iterations"));

    ObjectTypeDB::bind_method(_MD("get_gravity"), &ChipmunkSpace::get_gravity);
    ObjectTypeDB::bind_method(_MD("set_gravity", "gravity:Vector2"), &ChipmunkSpace::set_gravity);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "gravity"), _SCS("set_gravity"), _SCS("get_gravity"));

    ObjectTypeDB::bind_method(_MD("get_damping"), &ChipmunkSpace::get_damping);
    ObjectTypeDB::bind_method(_MD("set_damping", "damping:real"), &ChipmunkSpace::set_damping);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "damping"), _SCS("set_damping"), _SCS("get_damping"));

    ObjectTypeDB::bind_method(_MD("get_idle_speed_threshold"), &ChipmunkSpace::get_idle_speed_threshold);
    ObjectTypeDB::bind_method(_MD("set_idle_speed_threshold", "idle_speed_threshold:real"), &ChipmunkSpace::set_idle_speed_threshold);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "idle_speed_threshold"), _SCS("set_idle_speed_threshold"), _SCS("get_idle_speed_threshold"));

    ObjectTypeDB::bind_method(_MD("get_sleep_time_threshold"), &ChipmunkSpace::get_sleep_time_threshold);
    ObjectTypeDB::bind_method(_MD("set_sleep_time_threshold", "sleep_time_threshold:real"), &ChipmunkSpace::set_sleep_time_threshold);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "sleep_time_threshold"), _SCS("set_sleep_time_threshold"), _SCS("get_sleep_time_threshold"));

    ObjectTypeDB::bind_method(_MD("get_collision_slop"), &ChipmunkSpace::get_collision_slop);
    ObjectTypeDB::bind_method(_MD("set_collision_slop", "collision_slop:real"), &ChipmunkSpace::set_collision_slop);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "collision_slop"), _SCS("set_collision_slop"), _SCS("get_collision_slop"));

    ObjectTypeDB::bind_method(_MD("get_collision_bias"), &ChipmunkSpace::get_collision_bias);
    ObjectTypeDB::bind_method(_MD("set_collision_bias", "collision_bias:real"), &ChipmunkSpace::set_collision_bias);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "collision_bias"), _SCS("set_collision_bias"), _SCS("get_collision_bias"));

    ObjectTypeDB::bind_method(_MD("get_collision_persistence"), &ChipmunkSpace::get_collision_persistence);
    ObjectTypeDB::bind_method(_MD("set_collision_persistence", "collision_persistence:real"), &ChipmunkSpace::set_collision_persistence);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "collision_persistence"), _SCS("set_collision_persistence"), _SCS("get_collision_persistence"));

    ObjectTypeDB::bind_method(_MD("get_metadata"), &ChipmunkSpace::get_metadata);
    ObjectTypeDB::bind_method(_MD("set_metadata", "metadata:Variant"), &ChipmunkSpace::set_metadata);

    ObjectTypeDB::bind_method(_MD("get_current_timestep"), &ChipmunkSpace::get_current_timestep);
    ObjectTypeDB::bind_method(_MD("is_locked"), &ChipmunkSpace::is_locked);

    ObjectTypeDB::bind_method(_MD("add_default_collision_handler:ChipmunkCollisionHandler"), &ChipmunkSpace::add_default_collision_handler);
    ObjectTypeDB::bind_method(_MD("add_collision_handler:ChipmunkCollisionHandler", "type_a:int", "type_b:int"), &ChipmunkSpace::add_collision_handler);
    ObjectTypeDB::bind_method(_MD("add_wildcard_handler:ChipmunkCollisionHandler", "type:int"), &ChipmunkSpace::add_wildcard_handler);

    ObjectTypeDB::bind_method(_MD("add_body", "body:ChipmunkBody"), &ChipmunkSpace::add_body);
    ObjectTypeDB::bind_method(_MD("remove_body", "body:ChipmunkBody"), &ChipmunkSpace::remove_body);
    ObjectTypeDB::bind_method(_MD("contains_body", "body:ChipmunkBody"), &ChipmunkSpace::contains_body);

    ObjectTypeDB::bind_method(_MD("add_shape", "shape:ChipmunkShape"), &ChipmunkSpace::add_shape);
    ObjectTypeDB::bind_method(_MD("remove_shape", "shape:ChipmunkShape"), &ChipmunkSpace::remove_shape);
    ObjectTypeDB::bind_method(_MD("contains_shape", "shape:ChipmunkShape"), &ChipmunkSpace::contains_shape);

    ObjectTypeDB::bind_method(_MD("add_constraint", "constraint:ChipmunkConstraint"), &ChipmunkSpace::add_constraint);
    ObjectTypeDB::bind_method(_MD("remove_constraint", "constraint:ChipmunkConstraint"), &ChipmunkSpace::remove_constraint);
    ObjectTypeDB::bind_method(_MD("contains_constraint", "constraint:ChipmunkConstraint"), &ChipmunkSpace::contains_constraint);

    ObjectTypeDB::bind_method(_MD("point_query", "point:Vector2", "maxDistance:real", "filter:ChipmunkShapeFilter"), &ChipmunkSpace::point_query);
    ObjectTypeDB::bind_method(_MD("point_query_nearest", "point:Vector2", "maxDistance:real", "filter:ChipmunkShapeFilter"), &ChipmunkSpace::point_query_nearest);

    ObjectTypeDB::bind_method(_MD("step", "dt:real"), &ChipmunkSpace::step);
}

ChipmunkSpace *ChipmunkSpace::get(const cpSpace *space)
{
    auto id = space ? cpSpaceGetUserData(space) : 0;
    return (ChipmunkSpace*)ObjectDB::get_instance(id);
}
