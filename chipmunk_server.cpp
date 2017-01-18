
#include "chipmunk_server.h"
#include "print_string.h"

ChipmunkServer *ChipmunkServer::singleton = NULL;

/**********************************************************************/
// Math type conversion

static inline cpVect CP(const Vector2 &v) { return cpv(v.x, v.y); }
static inline cpBB CP(const Rect2 &v) { return cpBBNew(v.pos.x, v.pos.y, v.pos.x + v.size.x, v.pos.y + v.size.y); }

static inline cpTransform CP(const Matrix32 &v)
{
    return cpTransform
    {
        v.elements[0].x, v.elements[0].y,
        v.elements[1].x, v.elements[1].y,
        v.elements[2].x, v.elements[2].y
    };
}

static inline Vector2 GD(const cpVect &v) { return Vector2(v.x, v.y); }
static inline Rect2 GD(const cpBB &v) { return Rect2(v.l, v.b, v.r - v.l, v.t - v.b); }

static inline Matrix32 GD(const cpTransform &v)
{
    return Matrix32(v.a, v.b, v.c, v.d, v.tx, v.ty);
}

/**********************************************************************/
// Space

RID ChipmunkServer::space_new()
{
    auto space = cpSpaceNew();
    auto rid = space_owner.make_rid(space);
    auto data = data_pool.push_back(GodotData(rid));
    cpSpaceSetUserData(space, data);
    return rid;
}

void ChipmunkServer::space_free(RID p_rid)
{
    auto space = space_owner.get(p_rid);
    auto data = (GodotDataRef*)cpSpaceGetUserData(space);
    data_pool.erase(data);
    space_owner.free(p_rid);
    cpSpaceFree(space);
}

int ChipmunkServer::space_get_iterations(RID p_space)
{
	auto *space = space_owner.get(p_space);
	return cpSpaceGetIterations(space);
}

void ChipmunkServer::space_set_iterations(RID p_space, int p_iterations)
{
	auto *space = space_owner.get(p_space);
	cpSpaceSetIterations(space, p_iterations);
}

Vector2 ChipmunkServer::space_get_gravity(RID p_space)
{
	auto *space = space_owner.get(p_space);
	return GD(cpSpaceGetGravity(space));
}

void ChipmunkServer::space_set_gravity(RID p_space, Vector2 p_gravity)
{
	auto *space = space_owner.get(p_space);
	cpSpaceSetGravity(space, CP(p_gravity));
}

float ChipmunkServer::space_get_damping(RID p_space)
{
	auto *space = space_owner.get(p_space);
	return cpSpaceGetDamping(space);
}

void ChipmunkServer::space_set_damping(RID p_space, float p_damping)
{
	auto *space = space_owner.get(p_space);
	cpSpaceSetDamping(space, p_damping);
}

float ChipmunkServer::space_get_idle_speed_threshold(RID p_space)
{
	auto *space = space_owner.get(p_space);
	return cpSpaceGetIdleSpeedThreshold(space);
}

void ChipmunkServer::space_set_idle_speed_threshold(RID p_space, float p_idleSpeedThreshold)
{
	auto *space = space_owner.get(p_space);
	cpSpaceSetIdleSpeedThreshold(space, p_idleSpeedThreshold);
}

float ChipmunkServer::space_get_sleep_time_threshold(RID p_space)
{
	auto *space = space_owner.get(p_space);
	return cpSpaceGetSleepTimeThreshold(space);
}

void ChipmunkServer::space_set_sleep_time_threshold(RID p_space, float p_sleepTimeThreshold)
{
	auto *space = space_owner.get(p_space);
	cpSpaceSetSleepTimeThreshold(space, p_sleepTimeThreshold);
}

float ChipmunkServer::space_get_collision_slop(RID p_space)
{
	auto *space = space_owner.get(p_space);
	return cpSpaceGetCollisionSlop(space);
}

void ChipmunkServer::space_set_collision_slop(RID p_space, float p_collisionSlop)
{
	auto *space = space_owner.get(p_space);
	cpSpaceSetCollisionSlop(space, p_collisionSlop);
}

float ChipmunkServer::space_get_collision_bias(RID p_space)
{
	auto *space = space_owner.get(p_space);
	return cpSpaceGetCollisionBias(space);
}

void ChipmunkServer::space_set_collision_bias(RID p_space, float p_collisionBias)
{
	auto *space = space_owner.get(p_space);
	cpSpaceSetCollisionBias(space, p_collisionBias);
}

int ChipmunkServer::space_get_collision_persistence(RID p_space)
{
	auto *space = space_owner.get(p_space);
	return cpSpaceGetCollisionPersistence(space);
}

void ChipmunkServer::space_set_collision_persistence(RID p_space, int p_collisionPersistence)
{
	auto *space = space_owner.get(p_space);
	cpSpaceSetCollisionPersistence(space, p_collisionPersistence);
}

float ChipmunkServer::space_get_current_time_step(RID p_space)
{
	auto *space = space_owner.get(p_space);
	return cpSpaceGetCurrentTimeStep(space);
}

bool ChipmunkServer::space_is_locked(RID p_space)
{
	auto *space = space_owner.get(p_space);
	return cpSpaceIsLocked(space);
}

RID ChipmunkServer::space_add_shape(RID p_space, RID p_shape)
{
	auto *space = space_owner.get(p_space);
	auto *shape = shape_owner.get(p_shape);
	cpSpaceAddShape(space, shape);
    return p_shape;
}

RID ChipmunkServer::space_add_body(RID p_space, RID p_body)
{
	auto *space = space_owner.get(p_space);
	auto *body = body_owner.get(p_body);
	cpSpaceAddBody(space, body);
    return p_body;
}

RID ChipmunkServer::space_add_constraint(RID p_space, RID p_constraint)
{
	auto *space = space_owner.get(p_space);
	auto *constraint = constraint_owner.get(p_constraint);
	cpSpaceAddConstraint(space, constraint);
    return p_constraint;
}

void ChipmunkServer::space_remove_shape(RID p_space, RID p_shape)
{
	auto *space = space_owner.get(p_space);
	auto *shape = shape_owner.get(p_shape);
	cpSpaceRemoveShape(space, shape);
}

void ChipmunkServer::space_remove_body(RID p_space, RID p_body)
{
	auto *space = space_owner.get(p_space);
	auto *body = body_owner.get(p_body);
	cpSpaceRemoveBody(space, body);
}

void ChipmunkServer::space_remove_constraint(RID p_space, RID p_constraint)
{
	auto *space = space_owner.get(p_space);
	auto *constraint = constraint_owner.get(p_constraint);
	cpSpaceRemoveConstraint(space, constraint);
}

bool ChipmunkServer::space_contains_shape(RID p_space, RID p_shape)
{
	auto *space = space_owner.get(p_space);
	auto *shape = shape_owner.get(p_shape);
	return cpSpaceContainsShape(space, shape);
}

bool ChipmunkServer::space_contains_body(RID p_space, RID p_body)
{
	auto *space = space_owner.get(p_space);
	auto *body = body_owner.get(p_body);
	return cpSpaceContainsBody(space, body);
}

bool ChipmunkServer::space_contains_constraint(RID p_space, RID p_constraint)
{
	auto *space = space_owner.get(p_space);
	auto *constraint = constraint_owner.get(p_constraint);
	return cpSpaceContainsConstraint(space, constraint);
}

void ChipmunkServer::space_reindex_static(RID p_space)
{
	auto *space = space_owner.get(p_space);
	cpSpaceReindexStatic(space);
}

void ChipmunkServer::space_reindex_shape(RID p_space, RID p_shape)
{
	auto *space = space_owner.get(p_space);
	auto *shape = shape_owner.get(p_shape);
	cpSpaceReindexShape(space, shape);
}

void ChipmunkServer::space_reindex_shapes_for_body(RID p_space, RID p_body)
{
	auto *space = space_owner.get(p_space);
	auto *body = body_owner.get(p_body);
	cpSpaceReindexShapesForBody(space, body);
}

void ChipmunkServer::space_use_spatial_hash(RID p_space, float p_dim, int p_count)
{
	auto *space = space_owner.get(p_space);
	cpSpaceUseSpatialHash(space, p_dim, p_count);
}

void ChipmunkServer::space_step(RID p_space, float p_dt)
{
	auto *space = space_owner.get(p_space);
	cpSpaceStep(space, p_dt);
}

/**********************************************************************/
// Body

RID ChipmunkServer::body_new(float p_mass, float p_moment)
{
    auto body = cpBodyNew(p_mass, p_moment);
    auto rid = body_owner.make_rid(body);
    auto data = data_pool.push_back(GodotData(rid));
    cpBodySetUserData(body, data);
    return rid;
}

RID ChipmunkServer::body_new_kinematic()
{
    auto body = cpBodyNewKinematic();
    auto rid = body_owner.make_rid(body);
    auto data = data_pool.push_back(GodotData(rid));
    cpBodySetUserData(body, data);
    return rid;
}

RID ChipmunkServer::body_new_static()
{
    auto body = cpBodyNewStatic();
    auto rid = body_owner.make_rid(body);
    auto data = data_pool.push_back(GodotData(rid));
    cpBodySetUserData(body, data);
    return rid;
}

void ChipmunkServer::body_free(RID p_body)
{
    auto *body = body_owner.get(p_body);
    auto *data = (GodotDataRef*)cpBodyGetUserData(body);
    data_pool.erase(data);
    body_owner.free(p_body);
	cpBodyFree(body);
}

void ChipmunkServer::body_activate(RID p_body)
{
	auto *body = body_owner.get(p_body);
	cpBodyActivate(body);
}

void ChipmunkServer::body_activate_static(RID p_body, RID p_filter)
{
	auto *body = body_owner.get(p_body);
	auto *filter = shape_owner.get(p_filter);
	cpBodyActivateStatic(body, filter);
}

void ChipmunkServer::body_sleep(RID p_body)
{
	auto *body = body_owner.get(p_body);
	cpBodySleep(body);
}

void ChipmunkServer::body_sleep_with_group(RID p_body, RID p_group)
{
	auto *body = body_owner.get(p_body);
	auto *group = body_owner.get(p_group);
	cpBodySleepWithGroup(body, group);
}

bool ChipmunkServer::body_is_sleeping(RID p_body)
{
	auto *body = body_owner.get(p_body);
	return cpBodyIsSleeping(body);
}

int ChipmunkServer::body_get_type(RID p_body)
{
	auto *body = body_owner.get(p_body);
	return cpBodyGetType(body);
}

void ChipmunkServer::body_set_type(RID p_body, int p_type)
{
	auto *body = body_owner.get(p_body);
    cpBodySetType(body, static_cast<cpBodyType>(p_type));
}

RID ChipmunkServer::body_get_space(RID p_body)
{
	auto *body = body_owner.get(p_body);
    auto *space = cpBodyGetSpace(body);
    if (!space) return RID();
    auto data = (GodotDataRef*)cpSpaceGetUserData(space);
	return data->get().rid;
}

float ChipmunkServer::body_get_mass(RID p_body)
{
	auto *body = body_owner.get(p_body);
	return cpBodyGetMass(body);
}

void ChipmunkServer::body_set_mass(RID p_body, float p_m)
{
	auto *body = body_owner.get(p_body);
	cpBodySetMass(body, p_m);
}

float ChipmunkServer::body_get_moment(RID p_body)
{
	auto *body = body_owner.get(p_body);
	return cpBodyGetMoment(body);
}

void ChipmunkServer::body_set_moment(RID p_body, float p_i)
{
	auto *body = body_owner.get(p_body);
	cpBodySetMoment(body, p_i);
}

Vector2 ChipmunkServer::body_get_position(RID p_body)
{
	auto *body = body_owner.get(p_body);
	return GD(cpBodyGetPosition(body));
}

void ChipmunkServer::body_set_position(RID p_body, Vector2 p_pos)
{
	auto *body = body_owner.get(p_body);
	cpBodySetPosition(body, CP(p_pos));
}

Vector2 ChipmunkServer::body_get_center_of_gravity(RID p_body)
{
	auto *body = body_owner.get(p_body);
	return GD(cpBodyGetCenterOfGravity(body));
}

void ChipmunkServer::body_set_center_of_gravity(RID p_body, Vector2 p_cog)
{
	auto *body = body_owner.get(p_body);
	cpBodySetCenterOfGravity(body, CP(p_cog));
}

Vector2 ChipmunkServer::body_get_velocity(RID p_body)
{
	auto *body = body_owner.get(p_body);
	return GD(cpBodyGetVelocity(body));
}

void ChipmunkServer::body_set_velocity(RID p_body, Vector2 p_velocity)
{
	auto *body = body_owner.get(p_body);
	cpBodySetVelocity(body, CP(p_velocity));
}

Vector2 ChipmunkServer::body_get_force(RID p_body)
{
	auto *body = body_owner.get(p_body);
	return GD(cpBodyGetForce(body));
}

void ChipmunkServer::body_set_force(RID p_body, Vector2 p_force)
{
	auto *body = body_owner.get(p_body);
	cpBodySetForce(body, CP(p_force));
}

float ChipmunkServer::body_get_angle(RID p_body)
{
	auto *body = body_owner.get(p_body);
	return cpBodyGetAngle(body);
}

void ChipmunkServer::body_set_angle(RID p_body, float p_a)
{
	auto *body = body_owner.get(p_body);
	cpBodySetAngle(body, p_a);
}

float ChipmunkServer::body_get_angular_velocity(RID p_body)
{
	auto *body = body_owner.get(p_body);
	return cpBodyGetAngularVelocity(body);
}

void ChipmunkServer::body_set_angular_velocity(RID p_body, float p_angularVelocity)
{
	auto *body = body_owner.get(p_body);
	cpBodySetAngularVelocity(body, p_angularVelocity);
}

float ChipmunkServer::body_get_torque(RID p_body)
{
	auto *body = body_owner.get(p_body);
	return cpBodyGetTorque(body);
}

void ChipmunkServer::body_set_torque(RID p_body, float p_torque)
{
	auto *body = body_owner.get(p_body);
	cpBodySetTorque(body, p_torque);
}

Vector2 ChipmunkServer::body_get_rotation(RID p_body)
{
	auto *body = body_owner.get(p_body);
	return GD(cpBodyGetRotation(body));
}

void ChipmunkServer::body_update_velocity(RID p_body, Vector2 p_gravity, float p_damping, float p_dt)
{
	auto *body = body_owner.get(p_body);
	cpBodyUpdateVelocity(body, CP(p_gravity), p_damping, p_dt);
}

void ChipmunkServer::body_update_position(RID p_body, float p_dt)
{
	auto *body = body_owner.get(p_body);
	cpBodyUpdatePosition(body, p_dt);
}

Vector2 ChipmunkServer::body_local_to_world(RID p_body, Vector2 p_point)
{
	auto *body = body_owner.get(p_body);
	return GD(cpBodyLocalToWorld(body, CP(p_point)));
}

Vector2 ChipmunkServer::body_world_to_local(RID p_body, Vector2 p_point)
{
	auto *body = body_owner.get(p_body);
	return GD(cpBodyWorldToLocal(body, CP(p_point)));
}

void ChipmunkServer::body_apply_force_at_world_point(RID p_body, Vector2 p_force, Vector2 p_point)
{
	auto *body = body_owner.get(p_body);
	cpBodyApplyForceAtWorldPoint(body, CP(p_force), CP(p_point));
}

void ChipmunkServer::body_apply_force_at_local_point(RID p_body, Vector2 p_force, Vector2 p_point)
{
	auto *body = body_owner.get(p_body);
	cpBodyApplyForceAtLocalPoint(body, CP(p_force), CP(p_point));
}

void ChipmunkServer::body_apply_impulse_at_world_point(RID p_body, Vector2 p_impulse, Vector2 p_point)
{
	auto *body = body_owner.get(p_body);
	cpBodyApplyImpulseAtWorldPoint(body, CP(p_impulse), CP(p_point));
}

void ChipmunkServer::body_apply_impulse_at_local_point(RID p_body, Vector2 p_impulse, Vector2 p_point)
{
	auto *body = body_owner.get(p_body);
	cpBodyApplyImpulseAtLocalPoint(body, CP(p_impulse), CP(p_point));
}

Vector2 ChipmunkServer::body_get_velocity_at_world_point(RID p_body, Vector2 p_point)
{
	auto *body = body_owner.get(p_body);
	return GD(cpBodyGetVelocityAtWorldPoint(body, CP(p_point)));
}

Vector2 ChipmunkServer::body_get_velocity_at_local_point(RID p_body, Vector2 p_point)
{
	auto *body = body_owner.get(p_body);
	return GD(cpBodyGetVelocityAtLocalPoint(body, CP(p_point)));
}

float ChipmunkServer::body_kinetic_energy(RID p_body)
{
	auto *body = body_owner.get(p_body);
	return cpBodyKineticEnergy(body);
}

/**********************************************************************/
// Shape

void ChipmunkServer::shape_free(RID p_shape)
{
    auto *shape = shape_owner.get(p_shape);
    auto *data = (GodotDataRef*)cpShapeGetUserData(shape);
    data_pool.erase(data);
    shape_owner.free(p_shape);
	cpShapeFree(shape);
}

Rect2 ChipmunkServer::shape_cache_bb(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return GD(cpShapeCacheBB(shape));
}

Rect2 ChipmunkServer::shape_update(RID p_shape, Matrix32 p_transform)
{
	auto *shape = shape_owner.get(p_shape);
	return GD(cpShapeUpdate(shape, CP(p_transform)));
}

RID ChipmunkServer::shape_get_space(RID p_shape)
{
    auto *shape = shape_owner.get(p_shape);
    auto *space = cpShapeGetSpace(shape);
    if (!space) return RID();
    auto *data = (GodotDataRef*)cpSpaceGetUserData(space);
	return data->get().rid;
}

RID ChipmunkServer::shape_get_body(RID p_shape)
{
    auto *shape = shape_owner.get(p_shape);
    auto *body = cpShapeGetBody(shape);
    if (!body) return RID();
    auto *data = (GodotDataRef*)cpBodyGetUserData(body);
	return data->get().rid;
}

void ChipmunkServer::shape_set_body(RID p_shape, RID p_body)
{
	auto *shape = shape_owner.get(p_shape);
	auto *body = body_owner.get(p_body);
	cpShapeSetBody(shape, body);
}

float ChipmunkServer::shape_get_mass(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return cpShapeGetMass(shape);
}

void ChipmunkServer::shape_set_mass(RID p_shape, float p_mass)
{
	auto *shape = shape_owner.get(p_shape);
	cpShapeSetMass(shape, p_mass);
}

float ChipmunkServer::shape_get_density(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return cpShapeGetDensity(shape);
}

void ChipmunkServer::shape_set_density(RID p_shape, float p_density)
{
	auto *shape = shape_owner.get(p_shape);
	cpShapeSetDensity(shape, p_density);
}

float ChipmunkServer::shape_get_moment(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return cpShapeGetMoment(shape);
}

float ChipmunkServer::shape_get_area(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return cpShapeGetArea(shape);
}

Vector2 ChipmunkServer::shape_get_center_of_gravity(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return GD(cpShapeGetCenterOfGravity(shape));
}

Rect2 ChipmunkServer::shape_get_bb(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return GD(cpShapeGetBB(shape));
}

bool ChipmunkServer::shape_get_sensor(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return cpShapeGetSensor(shape);
}

void ChipmunkServer::shape_set_sensor(RID p_shape, bool p_sensor)
{
	auto *shape = shape_owner.get(p_shape);
	cpShapeSetSensor(shape, p_sensor);
}

float ChipmunkServer::shape_get_elasticity(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return cpShapeGetElasticity(shape);
}

void ChipmunkServer::shape_set_elasticity(RID p_shape, float p_elasticity)
{
	auto *shape = shape_owner.get(p_shape);
	cpShapeSetElasticity(shape, p_elasticity);
}

float ChipmunkServer::shape_get_friction(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return cpShapeGetFriction(shape);
}

void ChipmunkServer::shape_set_friction(RID p_shape, float p_friction)
{
	auto *shape = shape_owner.get(p_shape);
	cpShapeSetFriction(shape, p_friction);
}

Vector2 ChipmunkServer::shape_get_surface_velocity(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return GD(cpShapeGetSurfaceVelocity(shape));
}

void ChipmunkServer::shape_set_surface_velocity(RID p_shape, Vector2 p_surfaceVelocity)
{
	auto *shape = shape_owner.get(p_shape);
	cpShapeSetSurfaceVelocity(shape, CP(p_surfaceVelocity));
}

int ChipmunkServer::shape_get_collision_type(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return cpShapeGetCollisionType(shape);
}

void ChipmunkServer::shape_set_collision_type(RID p_shape, int p_collisionType)
{
	auto *shape = shape_owner.get(p_shape);
	cpShapeSetCollisionType(shape, p_collisionType);
}

RID ChipmunkServer::circle_shape_new(RID p_body, float p_radius, Vector2 p_offset)
{
    auto *body = body_owner.get(p_body);
    auto *shape = cpCircleShapeNew(body, p_radius, CP(p_offset));
    auto rid = shape_owner.make_rid(shape);
    auto *data = data_pool.push_back(GodotData(rid));
    cpShapeSetUserData(shape, data);
    return rid;
}

Vector2 ChipmunkServer::circle_shape_get_offset(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return GD(cpCircleShapeGetOffset(shape));
}

float ChipmunkServer::circle_shape_get_radius(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return cpCircleShapeGetRadius(shape);
}

RID ChipmunkServer::segment_shape_new(RID p_body, Vector2 p_a, Vector2 p_b, float p_radius)
{
    auto *body = body_owner.get(p_body);
    auto *shape = cpSegmentShapeNew(body, CP(p_a), CP(p_b), p_radius);
    auto rid = shape_owner.make_rid(shape);
    auto *data = data_pool.push_back(GodotData(rid));
    cpShapeSetUserData(shape, data);
    return rid;
}

void ChipmunkServer::segment_shape_set_neighbors(RID p_shape, Vector2 p_prev, Vector2 p_next)
{
	auto *shape = shape_owner.get(p_shape);
	cpSegmentShapeSetNeighbors(shape, CP(p_prev), CP(p_next));
}

Vector2 ChipmunkServer::segment_shape_get_a(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return GD(cpSegmentShapeGetA(shape));
}

Vector2 ChipmunkServer::segment_shape_get_b(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return GD(cpSegmentShapeGetB(shape));
}

Vector2 ChipmunkServer::segment_shape_get_normal(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return GD(cpSegmentShapeGetNormal(shape));
}

float ChipmunkServer::segment_shape_get_radius(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return cpSegmentShapeGetRadius(shape);
}

/**********************************************************************/
// PolyShape

RID ChipmunkServer::poly_shape_new(RID p_body, const Vector2Array &p_verts, Matrix32 p_transform, float p_radius)
{
    Vector2Array::Read verts = p_verts.read();
    auto *body = body_owner.get(p_body);
    auto *shape = cpPolyShapeNew(body, p_verts.size(), reinterpret_cast<const cpVect*>(verts.ptr()), CP(p_transform), p_radius);
    auto rid = shape_owner.make_rid(shape);
    auto *data = data_pool.push_back(GodotData(rid));
    cpShapeSetUserData(shape, data);
    return rid;
}

RID ChipmunkServer::poly_shape_new_raw(RID p_body, const Vector2Array &p_verts, float p_radius)
{
    Vector2Array::Read verts = p_verts.read();
    auto *body = body_owner.get(p_body);
    auto *shape = cpPolyShapeNewRaw(body, p_verts.size(), reinterpret_cast<const cpVect*>(verts.ptr()), p_radius);
    auto rid = shape_owner.make_rid(shape);
    auto *data = data_pool.push_back(GodotData(rid));
    cpShapeSetUserData(shape, data);
    return rid;
}

RID ChipmunkServer::box_shape_new(RID p_body, float p_width, float p_height, float p_radius)
{
    auto *body = body_owner.get(p_body);
    auto *shape = cpBoxShapeNew(body, p_width, p_height, p_radius);
    auto rid = shape_owner.make_rid(shape);
    auto *data = data_pool.push_back(GodotData(rid));
    cpShapeSetUserData(shape, data);
    return rid;
}

RID ChipmunkServer::box_shape_new2(RID p_body, Rect2 p_box, float p_radius)
{
    auto *body = body_owner.get(p_body);
    auto *shape = cpBoxShapeNew2(body, CP(p_box), p_radius);
    auto rid = shape_owner.make_rid(shape);
    auto *data = data_pool.push_back(GodotData(rid));
    cpShapeSetUserData(shape, data);
    return rid;
}

int ChipmunkServer::poly_shape_get_count(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return cpPolyShapeGetCount(shape);
}

Vector2 ChipmunkServer::poly_shape_get_vert(RID p_shape, int p_index)
{
	auto *shape = shape_owner.get(p_shape);
	return GD(cpPolyShapeGetVert(shape, p_index));
}

float ChipmunkServer::poly_shape_get_radius(RID p_shape)
{
	auto *shape = shape_owner.get(p_shape);
	return cpPolyShapeGetRadius(shape);
}

/**********************************************************************/
// Constraint

void ChipmunkServer::constraint_free(RID p_constraint)
{
    auto *constraint = constraint_owner.get(p_constraint);
    auto *data = (GodotDataRef*)cpConstraintGetUserData(constraint);
    data_pool.erase(data);
    constraint_owner.free(p_constraint);
	cpConstraintFree(constraint);
}

RID ChipmunkServer::constraint_get_space(RID p_constraint)
{
    auto *constraint = constraint_owner.get(p_constraint);
    auto *space = cpConstraintGetSpace(constraint);
    if (!space) return RID();
    auto *data = (GodotDataRef*)cpSpaceGetUserData(space);
	return data->get().rid;
}

RID ChipmunkServer::constraint_get_body_a(RID p_constraint)
{
    auto *constraint = constraint_owner.get(p_constraint);
    auto *body = cpConstraintGetBodyA(constraint);
    if (!body) return RID();
    auto *data = (GodotDataRef*)cpBodyGetUserData(body);
	return data->get().rid;
}

RID ChipmunkServer::constraint_get_body_b(RID p_constraint)
{
    auto *constraint = constraint_owner.get(p_constraint);
    auto *body = cpConstraintGetBodyB(constraint);
    if (!body) return RID();
    auto *data = (GodotDataRef*)cpBodyGetUserData(body);
	return data->get().rid;
}

float ChipmunkServer::constraint_get_max_force(RID p_constraint)
{
	auto *constraint = constraint_owner.get(p_constraint);
	return cpConstraintGetMaxForce(constraint);
}

void ChipmunkServer::constraint_set_max_force(RID p_constraint, float p_maxForce)
{
	auto *constraint = constraint_owner.get(p_constraint);
	cpConstraintSetMaxForce(constraint, p_maxForce);
}

float ChipmunkServer::constraint_get_error_bias(RID p_constraint)
{
	auto *constraint = constraint_owner.get(p_constraint);
	return cpConstraintGetErrorBias(constraint);
}

void ChipmunkServer::constraint_set_error_bias(RID p_constraint, float p_errorBias)
{
	auto *constraint = constraint_owner.get(p_constraint);
	cpConstraintSetErrorBias(constraint, p_errorBias);
}

float ChipmunkServer::constraint_get_max_bias(RID p_constraint)
{
	auto *constraint = constraint_owner.get(p_constraint);
	return cpConstraintGetMaxBias(constraint);
}

void ChipmunkServer::constraint_set_max_bias(RID p_constraint, float p_maxBias)
{
	auto *constraint = constraint_owner.get(p_constraint);
	cpConstraintSetMaxBias(constraint, p_maxBias);
}

bool ChipmunkServer::constraint_get_collide_bodies(RID p_constraint)
{
	auto *constraint = constraint_owner.get(p_constraint);
	return cpConstraintGetCollideBodies(constraint);
}

void ChipmunkServer::constraint_set_collide_bodies(RID p_constraint, bool p_collideBodies)
{
	auto *constraint = constraint_owner.get(p_constraint);
	cpConstraintSetCollideBodies(constraint, p_collideBodies);
}

float ChipmunkServer::constraint_get_impulse(RID p_constraint)
{
	auto *constraint = constraint_owner.get(p_constraint);
	return cpConstraintGetImpulse(constraint);
}

/**********************************************************************/
// Pin Joint

bool ChipmunkServer::constraint_is_pin_joint(RID p_constraint)
{
	auto *constraint = constraint_owner.get(p_constraint);
	return cpConstraintIsPinJoint(constraint);
}

RID ChipmunkServer::pin_joint_new(RID p_a, RID p_b, Vector2 p_anchorA, Vector2 p_anchorB)
{
    auto *a = body_owner.get(p_a);
	auto *b = body_owner.get(p_b);
    auto *constraint = cpPinJointNew(a, b, CP(p_anchorA), CP(p_anchorB));
    auto rid = constraint_owner.make_rid(constraint);
    auto *data = data_pool.push_back(GodotData(rid));
    cpConstraintSetUserData(constraint, data);
    return rid;
}

Vector2 ChipmunkServer::pin_joint_get_anchor_a(RID p_constraint)
{
	auto *constraint = constraint_owner.get(p_constraint);
	return GD(cpPinJointGetAnchorA(constraint));
}

void ChipmunkServer::pin_joint_set_anchor_a(RID p_constraint, Vector2 p_anchorA)
{
	auto *constraint = constraint_owner.get(p_constraint);
	cpPinJointSetAnchorA(constraint, CP(p_anchorA));
}

Vector2 ChipmunkServer::pin_joint_get_anchor_b(RID p_constraint)
{
	auto *constraint = constraint_owner.get(p_constraint);
	return GD(cpPinJointGetAnchorB(constraint));
}

void ChipmunkServer::pin_joint_set_anchor_b(RID p_constraint, Vector2 p_anchorB)
{
	auto *constraint = constraint_owner.get(p_constraint);
	cpPinJointSetAnchorB(constraint, CP(p_anchorB));
}

float ChipmunkServer::pin_joint_get_dist(RID p_constraint)
{
	auto *constraint = constraint_owner.get(p_constraint);
	return cpPinJointGetDist(constraint);
}

void ChipmunkServer::pin_joint_set_dist(RID p_constraint, float p_dist)
{
	auto *constraint = constraint_owner.get(p_constraint);
	cpPinJointSetDist(constraint, p_dist);
}

/**********************************************************************/
// Server stuff

void ChipmunkServer::_bind_methods()
{
    /** Space */
    ObjectTypeDB::bind_method(_MD("space_new"), &ChipmunkServer::space_new);
    ObjectTypeDB::bind_method(_MD("space_free", "space"), &ChipmunkServer::space_free);
    ObjectTypeDB::bind_method(_MD("space_get_iterations", "space"), &ChipmunkServer::space_get_iterations);
    ObjectTypeDB::bind_method(_MD("space_set_iterations", "space", "iterations"), &ChipmunkServer::space_set_iterations);
    ObjectTypeDB::bind_method(_MD("space_get_gravity", "space"), &ChipmunkServer::space_get_gravity);
    ObjectTypeDB::bind_method(_MD("space_set_gravity", "space", "gravity"), &ChipmunkServer::space_set_gravity);
    ObjectTypeDB::bind_method(_MD("space_get_damping", "space"), &ChipmunkServer::space_get_damping);
    ObjectTypeDB::bind_method(_MD("space_set_damping", "space", "damping"), &ChipmunkServer::space_set_damping);
    ObjectTypeDB::bind_method(_MD("space_get_idle_speed_threshold", "space"), &ChipmunkServer::space_get_idle_speed_threshold);
    ObjectTypeDB::bind_method(_MD("space_set_idle_speed_threshold", "space", "idleSpeedThreshold"), &ChipmunkServer::space_set_idle_speed_threshold);
    ObjectTypeDB::bind_method(_MD("space_get_sleep_time_threshold", "space"), &ChipmunkServer::space_get_sleep_time_threshold);
    ObjectTypeDB::bind_method(_MD("space_set_sleep_time_threshold", "space", "sleepTimeThreshold"), &ChipmunkServer::space_set_sleep_time_threshold);
    ObjectTypeDB::bind_method(_MD("space_get_collision_slop", "space"), &ChipmunkServer::space_get_collision_slop);
    ObjectTypeDB::bind_method(_MD("space_set_collision_slop", "space", "collisionSlop"), &ChipmunkServer::space_set_collision_slop);
    ObjectTypeDB::bind_method(_MD("space_get_collision_bias", "space"), &ChipmunkServer::space_get_collision_bias);
    ObjectTypeDB::bind_method(_MD("space_set_collision_bias", "space", "collisionBias"), &ChipmunkServer::space_set_collision_bias);
    ObjectTypeDB::bind_method(_MD("space_get_collision_persistence", "space"), &ChipmunkServer::space_get_collision_persistence);
    ObjectTypeDB::bind_method(_MD("space_set_collision_persistence", "space", "collisionPersistence"), &ChipmunkServer::space_set_collision_persistence);
    ObjectTypeDB::bind_method(_MD("space_get_current_time_step", "space"), &ChipmunkServer::space_get_current_time_step);
    ObjectTypeDB::bind_method(_MD("space_is_locked", "space"), &ChipmunkServer::space_is_locked);
    ObjectTypeDB::bind_method(_MD("space_add_shape", "space", "shape"), &ChipmunkServer::space_add_shape);
    ObjectTypeDB::bind_method(_MD("space_add_body", "space", "body"), &ChipmunkServer::space_add_body);
    ObjectTypeDB::bind_method(_MD("space_add_constraint", "space", "constraint"), &ChipmunkServer::space_add_constraint);
    ObjectTypeDB::bind_method(_MD("space_remove_shape", "space", "shape"), &ChipmunkServer::space_remove_shape);
    ObjectTypeDB::bind_method(_MD("space_remove_body", "space", "body"), &ChipmunkServer::space_remove_body);
    ObjectTypeDB::bind_method(_MD("space_remove_constraint", "space", "constraint"), &ChipmunkServer::space_remove_constraint);
    ObjectTypeDB::bind_method(_MD("space_contains_shape", "space", "shape"), &ChipmunkServer::space_contains_shape);
    ObjectTypeDB::bind_method(_MD("space_contains_body", "space", "body"), &ChipmunkServer::space_contains_body);
    ObjectTypeDB::bind_method(_MD("space_contains_constraint", "space", "constraint"), &ChipmunkServer::space_contains_constraint);
    ObjectTypeDB::bind_method(_MD("space_reindex_static", "space"), &ChipmunkServer::space_reindex_static);
    ObjectTypeDB::bind_method(_MD("space_reindex_shape", "space", "shape"), &ChipmunkServer::space_reindex_shape);
    ObjectTypeDB::bind_method(_MD("space_reindex_shapes_for_body", "space", "body"), &ChipmunkServer::space_reindex_shapes_for_body);
    ObjectTypeDB::bind_method(_MD("space_use_spatial_hash", "space", "dim", "count"), &ChipmunkServer::space_use_spatial_hash);
    ObjectTypeDB::bind_method(_MD("space_step", "space", "dt"), &ChipmunkServer::space_step);

    /** Body */
    ObjectTypeDB::bind_method(_MD("body_new", "mass", "moment"), &ChipmunkServer::body_new);
    ObjectTypeDB::bind_method(_MD("body_new_kinematic"), &ChipmunkServer::body_new_kinematic);
    ObjectTypeDB::bind_method(_MD("body_new_static"), &ChipmunkServer::body_new_static);
    ObjectTypeDB::bind_method(_MD("body_free", "body"), &ChipmunkServer::body_free);
    ObjectTypeDB::bind_method(_MD("body_activate", "body"), &ChipmunkServer::body_activate);
    ObjectTypeDB::bind_method(_MD("body_activate_static", "body", "filter"), &ChipmunkServer::body_activate_static);
    ObjectTypeDB::bind_method(_MD("body_sleep", "body"), &ChipmunkServer::body_sleep);
    ObjectTypeDB::bind_method(_MD("body_sleep_with_group", "body", "group"), &ChipmunkServer::body_sleep_with_group);
    ObjectTypeDB::bind_method(_MD("body_is_sleeping", "body"), &ChipmunkServer::body_is_sleeping);
    ObjectTypeDB::bind_method(_MD("body_get_type", "body"), &ChipmunkServer::body_get_type);
    ObjectTypeDB::bind_method(_MD("body_set_type", "body", "type"), &ChipmunkServer::body_set_type);
    ObjectTypeDB::bind_method(_MD("body_get_space", "body"), &ChipmunkServer::body_get_space);
    ObjectTypeDB::bind_method(_MD("body_get_mass", "body"), &ChipmunkServer::body_get_mass);
    ObjectTypeDB::bind_method(_MD("body_set_mass", "body", "m"), &ChipmunkServer::body_set_mass);
    ObjectTypeDB::bind_method(_MD("body_get_moment", "body"), &ChipmunkServer::body_get_moment);
    ObjectTypeDB::bind_method(_MD("body_set_moment", "body", "i"), &ChipmunkServer::body_set_moment);
    ObjectTypeDB::bind_method(_MD("body_get_position", "body"), &ChipmunkServer::body_get_position);
    ObjectTypeDB::bind_method(_MD("body_set_position", "body", "pos"), &ChipmunkServer::body_set_position);
    ObjectTypeDB::bind_method(_MD("body_get_center_of_gravity", "body"), &ChipmunkServer::body_get_center_of_gravity);
    ObjectTypeDB::bind_method(_MD("body_set_center_of_gravity", "body", "cog"), &ChipmunkServer::body_set_center_of_gravity);
    ObjectTypeDB::bind_method(_MD("body_get_velocity", "body"), &ChipmunkServer::body_get_velocity);
    ObjectTypeDB::bind_method(_MD("body_set_velocity", "body", "velocity"), &ChipmunkServer::body_set_velocity);
    ObjectTypeDB::bind_method(_MD("body_get_force", "body"), &ChipmunkServer::body_get_force);
    ObjectTypeDB::bind_method(_MD("body_set_force", "body", "force"), &ChipmunkServer::body_set_force);
    ObjectTypeDB::bind_method(_MD("body_get_angle", "body"), &ChipmunkServer::body_get_angle);
    ObjectTypeDB::bind_method(_MD("body_set_angle", "body", "a"), &ChipmunkServer::body_set_angle);
    ObjectTypeDB::bind_method(_MD("body_get_angular_velocity", "body"), &ChipmunkServer::body_get_angular_velocity);
    ObjectTypeDB::bind_method(_MD("body_set_angular_velocity", "body", "angularVelocity"), &ChipmunkServer::body_set_angular_velocity);
    ObjectTypeDB::bind_method(_MD("body_get_torque", "body"), &ChipmunkServer::body_get_torque);
    ObjectTypeDB::bind_method(_MD("body_set_torque", "body", "torque"), &ChipmunkServer::body_set_torque);
    ObjectTypeDB::bind_method(_MD("body_get_rotation", "body"), &ChipmunkServer::body_get_rotation);
    ObjectTypeDB::bind_method(_MD("body_update_velocity", "body", "gravity", "damping", "dt"), &ChipmunkServer::body_update_velocity);
    ObjectTypeDB::bind_method(_MD("body_update_position", "body", "dt"), &ChipmunkServer::body_update_position);
    ObjectTypeDB::bind_method(_MD("body_local_to_world", "body", "point"), &ChipmunkServer::body_local_to_world);
    ObjectTypeDB::bind_method(_MD("body_world_to_local", "body", "point"), &ChipmunkServer::body_world_to_local);
    ObjectTypeDB::bind_method(_MD("body_apply_force_at_world_point", "body", "force", "point"), &ChipmunkServer::body_apply_force_at_world_point);
    ObjectTypeDB::bind_method(_MD("body_apply_force_at_local_point", "body", "force", "point"), &ChipmunkServer::body_apply_force_at_local_point);
    ObjectTypeDB::bind_method(_MD("body_apply_impulse_at_world_point", "body", "impulse", "point"), &ChipmunkServer::body_apply_impulse_at_world_point);
    ObjectTypeDB::bind_method(_MD("body_apply_impulse_at_local_point", "body", "impulse", "point"), &ChipmunkServer::body_apply_impulse_at_local_point);
    ObjectTypeDB::bind_method(_MD("body_get_velocity_at_world_point", "body", "point"), &ChipmunkServer::body_get_velocity_at_world_point);
    ObjectTypeDB::bind_method(_MD("body_get_velocity_at_local_point", "body", "point"), &ChipmunkServer::body_get_velocity_at_local_point);
    ObjectTypeDB::bind_method(_MD("body_kinetic_energy", "body"), &ChipmunkServer::body_kinetic_energy);

    /** Shape */
    ObjectTypeDB::bind_method(_MD("shape_free", "shape"), &ChipmunkServer::shape_free);
    ObjectTypeDB::bind_method(_MD("shape_cache_bb", "shape"), &ChipmunkServer::shape_cache_bb);
    ObjectTypeDB::bind_method(_MD("shape_update", "shape", "transform"), &ChipmunkServer::shape_update);
    ObjectTypeDB::bind_method(_MD("shape_get_space", "shape"), &ChipmunkServer::shape_get_space);
    ObjectTypeDB::bind_method(_MD("shape_get_body", "shape"), &ChipmunkServer::shape_get_body);
    ObjectTypeDB::bind_method(_MD("shape_set_body", "shape", "body"), &ChipmunkServer::shape_set_body);
    ObjectTypeDB::bind_method(_MD("shape_get_mass", "shape"), &ChipmunkServer::shape_get_mass);
    ObjectTypeDB::bind_method(_MD("shape_set_mass", "shape", "mass"), &ChipmunkServer::shape_set_mass);
    ObjectTypeDB::bind_method(_MD("shape_get_density", "shape"), &ChipmunkServer::shape_get_density);
    ObjectTypeDB::bind_method(_MD("shape_set_density", "shape", "density"), &ChipmunkServer::shape_set_density);
    ObjectTypeDB::bind_method(_MD("shape_get_moment", "shape"), &ChipmunkServer::shape_get_moment);
    ObjectTypeDB::bind_method(_MD("shape_get_area", "shape"), &ChipmunkServer::shape_get_area);
    ObjectTypeDB::bind_method(_MD("shape_get_center_of_gravity", "shape"), &ChipmunkServer::shape_get_center_of_gravity);
    ObjectTypeDB::bind_method(_MD("shape_get_bb", "shape"), &ChipmunkServer::shape_get_bb);
    ObjectTypeDB::bind_method(_MD("shape_get_sensor", "shape"), &ChipmunkServer::shape_get_sensor);
    ObjectTypeDB::bind_method(_MD("shape_set_sensor", "shape", "sensor"), &ChipmunkServer::shape_set_sensor);
    ObjectTypeDB::bind_method(_MD("shape_get_elasticity", "shape"), &ChipmunkServer::shape_get_elasticity);
    ObjectTypeDB::bind_method(_MD("shape_set_elasticity", "shape", "elasticity"), &ChipmunkServer::shape_set_elasticity);
    ObjectTypeDB::bind_method(_MD("shape_get_friction", "shape"), &ChipmunkServer::shape_get_friction);
    ObjectTypeDB::bind_method(_MD("shape_set_friction", "shape", "friction"), &ChipmunkServer::shape_set_friction);
    ObjectTypeDB::bind_method(_MD("shape_get_surface_velocity", "shape"), &ChipmunkServer::shape_get_surface_velocity);
    ObjectTypeDB::bind_method(_MD("shape_set_surface_velocity", "shape", "surfaceVelocity"), &ChipmunkServer::shape_set_surface_velocity);
    ObjectTypeDB::bind_method(_MD("shape_get_collision_type", "shape"), &ChipmunkServer::shape_get_collision_type);
    ObjectTypeDB::bind_method(_MD("shape_set_collision_type", "shape", "collisionType"), &ChipmunkServer::shape_set_collision_type);
    ObjectTypeDB::bind_method(_MD("circle_shape_new", "body", "radius", "offset"), &ChipmunkServer::circle_shape_new);
    ObjectTypeDB::bind_method(_MD("circle_shape_get_offset", "shape"), &ChipmunkServer::circle_shape_get_offset);
    ObjectTypeDB::bind_method(_MD("circle_shape_get_radius", "shape"), &ChipmunkServer::circle_shape_get_radius);
    ObjectTypeDB::bind_method(_MD("segment_shape_new", "body", "a", "b", "radius"), &ChipmunkServer::segment_shape_new);
    ObjectTypeDB::bind_method(_MD("segment_shape_set_neighbors", "shape", "prev", "next"), &ChipmunkServer::segment_shape_set_neighbors);
    ObjectTypeDB::bind_method(_MD("segment_shape_get_a", "shape"), &ChipmunkServer::segment_shape_get_a);
    ObjectTypeDB::bind_method(_MD("segment_shape_get_b", "shape"), &ChipmunkServer::segment_shape_get_b);
    ObjectTypeDB::bind_method(_MD("segment_shape_get_normal", "shape"), &ChipmunkServer::segment_shape_get_normal);
    ObjectTypeDB::bind_method(_MD("segment_shape_get_radius", "shape"), &ChipmunkServer::segment_shape_get_radius);

    /** PolyShape */
    ObjectTypeDB::bind_method(_MD("poly_shape_new", "body", "verts", "transform", "radius"), &ChipmunkServer::poly_shape_new);
    ObjectTypeDB::bind_method(_MD("poly_shape_new_raw", "body", "verts", "radius"), &ChipmunkServer::poly_shape_new_raw);
    ObjectTypeDB::bind_method(_MD("box_shape_new", "body", "width", "height", "radius"), &ChipmunkServer::box_shape_new);
    ObjectTypeDB::bind_method(_MD("box_shape_new2", "body", "box", "radius"), &ChipmunkServer::box_shape_new2);
    ObjectTypeDB::bind_method(_MD("poly_shape_get_count", "shape"), &ChipmunkServer::poly_shape_get_count);
    ObjectTypeDB::bind_method(_MD("poly_shape_get_vert", "shape", "index"), &ChipmunkServer::poly_shape_get_vert);
    ObjectTypeDB::bind_method(_MD("poly_shape_get_radius", "shape"), &ChipmunkServer::poly_shape_get_radius);

    /** Constraint */
    ObjectTypeDB::bind_method(_MD("constraint_free", "constraint"), &ChipmunkServer::constraint_free);
    ObjectTypeDB::bind_method(_MD("constraint_get_space", "constraint"), &ChipmunkServer::constraint_get_space);
    ObjectTypeDB::bind_method(_MD("constraint_get_body_a", "constraint"), &ChipmunkServer::constraint_get_body_a);
    ObjectTypeDB::bind_method(_MD("constraint_get_body_b", "constraint"), &ChipmunkServer::constraint_get_body_b);
    ObjectTypeDB::bind_method(_MD("constraint_get_max_force", "constraint"), &ChipmunkServer::constraint_get_max_force);
    ObjectTypeDB::bind_method(_MD("constraint_set_max_force", "constraint", "maxForce"), &ChipmunkServer::constraint_set_max_force);
    ObjectTypeDB::bind_method(_MD("constraint_get_error_bias", "constraint"), &ChipmunkServer::constraint_get_error_bias);
    ObjectTypeDB::bind_method(_MD("constraint_set_error_bias", "constraint", "errorBias"), &ChipmunkServer::constraint_set_error_bias);
    ObjectTypeDB::bind_method(_MD("constraint_get_max_bias", "constraint"), &ChipmunkServer::constraint_get_max_bias);
    ObjectTypeDB::bind_method(_MD("constraint_set_max_bias", "constraint", "maxBias"), &ChipmunkServer::constraint_set_max_bias);
    ObjectTypeDB::bind_method(_MD("constraint_get_collide_bodies", "constraint"), &ChipmunkServer::constraint_get_collide_bodies);
    ObjectTypeDB::bind_method(_MD("constraint_set_collide_bodies", "constraint", "collideBodies"), &ChipmunkServer::constraint_set_collide_bodies);
    ObjectTypeDB::bind_method(_MD("constraint_get_impulse", "constraint"), &ChipmunkServer::constraint_get_impulse);

    /** Pin Joint */
    ObjectTypeDB::bind_method(_MD("constraint_is_pin_joint", "constraint"), &ChipmunkServer::constraint_is_pin_joint);
    ObjectTypeDB::bind_method(_MD("pin_joint_new", "a", "b", "anchorA", "anchorB"), &ChipmunkServer::pin_joint_new);
    ObjectTypeDB::bind_method(_MD("pin_joint_get_anchor_a", "constraint"), &ChipmunkServer::pin_joint_get_anchor_a);
    ObjectTypeDB::bind_method(_MD("pin_joint_set_anchor_a", "constraint", "anchorA"), &ChipmunkServer::pin_joint_set_anchor_a);
    ObjectTypeDB::bind_method(_MD("pin_joint_get_anchor_b", "constraint"), &ChipmunkServer::pin_joint_get_anchor_b);
    ObjectTypeDB::bind_method(_MD("pin_joint_set_anchor_b", "constraint", "anchorB"), &ChipmunkServer::pin_joint_set_anchor_b);
    ObjectTypeDB::bind_method(_MD("pin_joint_get_dist", "constraint"), &ChipmunkServer::pin_joint_get_dist);
    ObjectTypeDB::bind_method(_MD("pin_joint_set_dist", "constraint", "dist"), &ChipmunkServer::pin_joint_set_dist);
}

ChipmunkServer *ChipmunkServer::get_singleton()
{
    return singleton;
}

ChipmunkServer::ChipmunkServer()
{
    singleton = this;
    print_line("Chipmunk server is online");
}

ChipmunkServer::~ChipmunkServer()
{
    singleton = NULL;
}
