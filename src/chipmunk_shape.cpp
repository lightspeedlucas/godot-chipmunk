
#include <godot_chipmunk.h>
#include "chipmunk_shape.h"

ChipmunkShape::ChipmunkShape(cpShape *shape)
    : shape(shape)
{
    cpShapeSetUserData(shape, get_instance_ID());
}

ChipmunkShape::~ChipmunkShape()
{
    cpShapeFree(shape);
}

Rect2 ChipmunkShape::cache_bb()
{
    return GD(cpShapeCacheBB(shape));
}

Rect2 ChipmunkShape::update(const Matrix32 &value)
{
    return GD(cpShapeUpdate(shape, CP(value)));
}

Rect2 ChipmunkShape::get_bb() const
{
    return GD(cpShapeGetBB(shape));
}

Dictionary ChipmunkShape::point_query(const Vector2 &point) const
{
    cpPointQueryInfo info;
    cpShapePointQuery(shape, CP(point), &info);
    Dictionary r(true);
    r["shape"] = this;
    r["point"] = GD(info.point);
    r["distance"] = info.distance;
    r["gradient"] = GD(info.gradient);
    return r;
}

Dictionary ChipmunkShape::segment_query(const Vector2 &a, const Vector2 &b, float radius) const
{
    cpSegmentQueryInfo info;
    cpShapeSegmentQuery(shape, CP(a), CP(b), radius, &info);
    Dictionary r(true);
    r["shape"] = this;
    r["point"] = GD(info.point);
    r["normal"] = GD(info.normal);
    r["alpha"] = info.alpha;
    return r;
}

Dictionary ChipmunkShape::collide(ChipmunkShape *other) const
{
    Dictionary r(true);
    ERR_FAIL_NULL_V(other, r);
    auto set = cpShapesCollide(*this, *other);
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

ChipmunkSpace *ChipmunkShape::get_space() const
{
    return ChipmunkSpace::get(cpShapeGetSpace(shape));
}

ChipmunkBody *ChipmunkShape::get_body() const
{
    return ChipmunkBody::get(cpShapeGetBody(shape));
}

float ChipmunkShape::get_mass() const
{
    return cpShapeGetMass(shape);
}

void ChipmunkShape::set_mass(float value)
{
    cpShapeSetMass(shape, value);
}

float ChipmunkShape::get_density() const
{
    return cpShapeGetDensity(shape);
}

void ChipmunkShape::set_density(float value)
{
    cpShapeSetDensity(shape, value);
}

float ChipmunkShape::get_moment() const
{
    return cpShapeGetMoment(shape);
}

float ChipmunkShape::get_area() const
{
    return cpShapeGetArea(shape);
}

Vector2 ChipmunkShape::get_center_of_gravity() const
{
    return GD(cpShapeGetCenterOfGravity(shape));
}

bool ChipmunkShape::get_sensor() const
{
    return cpShapeGetSensor(shape);
}

void ChipmunkShape::set_sensor(bool value)
{
    cpShapeSetSensor(shape, value);
}

float ChipmunkShape::get_elasticity() const
{
    return cpShapeGetElasticity(shape);
}

void ChipmunkShape::set_elasticity(float value)
{
    cpShapeSetElasticity(shape, value);
}

float ChipmunkShape::get_friction() const
{
    return cpShapeGetFriction(shape);
}

void ChipmunkShape::set_friction(float value)
{
    cpShapeSetFriction(shape, value);
}

Vector2 ChipmunkShape::get_surface_velocity() const
{
    return GD(cpShapeGetSurfaceVelocity(shape));
}

void ChipmunkShape::set_surface_velocity(const Vector2 &value)
{
    cpShapeSetSurfaceVelocity(shape, CP(value));
}

Variant ChipmunkShape::get_metadata() const
{
    return metadata;
}

void ChipmunkShape::set_metadata(const Variant &value)
{
    metadata = value;
}

int ChipmunkShape::get_collision_type() const
{
    return cpShapeGetCollisionType(shape);
}

void ChipmunkShape::set_collision_type(int value)
{
    cpShapeSetCollisionType(shape, value);
}

Ref<ChipmunkShapeFilter> ChipmunkShape::get_filter() const
{
    return memnew(ChipmunkShapeFilter(cpShapeGetFilter(shape)));
}

void ChipmunkShape::set_filter(const Ref<ChipmunkShapeFilter> &filter)
{
    ERR_FAIL_COND(filter.is_null());
    cpShapeSetFilter(shape, **filter);
}

void ChipmunkShape::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("cache_bb:Rect2"), &ChipmunkShape::cache_bb);
    ObjectTypeDB::bind_method(_MD("update:Rect2", "transform:Matrix32"), &ChipmunkShape::update);
    ObjectTypeDB::bind_method(_MD("get_bb:Rect2"), &ChipmunkShape::get_bb);

    ObjectTypeDB::bind_method(_MD("point_query:Dictionary", "point:Vector2"), &ChipmunkShape::point_query);
    ObjectTypeDB::bind_method(_MD("segment_query:Dictionary", "a:Vector2", "b:Vector2", "radius:real"), &ChipmunkShape::segment_query, DEFVAL(.0f));

    ObjectTypeDB::bind_method(_MD("collide:Dictionary", "shape:ChipmunkShape"), &ChipmunkShape::collide);

    ObjectTypeDB::bind_method(_MD("get_space"), &ChipmunkShape::get_space);
    ObjectTypeDB::bind_method(_MD("get_body"), &ChipmunkShape::get_body);

    ObjectTypeDB::bind_method(_MD("get_mass"), &ChipmunkShape::get_mass);
    ObjectTypeDB::bind_method(_MD("set_mass", "mass:real"), &ChipmunkShape::set_mass);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "mass"), _SCS("set_mass"), _SCS("get_mass"));

    ObjectTypeDB::bind_method(_MD("get_density"), &ChipmunkShape::get_density);
    ObjectTypeDB::bind_method(_MD("set_density", "density:real"), &ChipmunkShape::set_density);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "density"), _SCS("set_density"), _SCS("get_density"));

    ObjectTypeDB::bind_method(_MD("get_moment:real"), &ChipmunkShape::get_moment);
    ObjectTypeDB::bind_method(_MD("get_area:real"), &ChipmunkShape::get_area);
    ObjectTypeDB::bind_method(_MD("get_center_of_gravity:Vector2"), &ChipmunkShape::get_center_of_gravity);

    ObjectTypeDB::bind_method(_MD("get_sensor"), &ChipmunkShape::get_sensor);
    ObjectTypeDB::bind_method(_MD("set_sensor", "sensor:bool"), &ChipmunkShape::set_sensor);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "sensor"), _SCS("set_sensor"), _SCS("get_sensor"));

    ObjectTypeDB::bind_method(_MD("get_elasticity"), &ChipmunkShape::get_elasticity);
    ObjectTypeDB::bind_method(_MD("set_elasticity", "elasticity:real"), &ChipmunkShape::set_elasticity);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "elasticity"), _SCS("set_elasticity"), _SCS("get_elasticity"));

    ObjectTypeDB::bind_method(_MD("get_friction"), &ChipmunkShape::get_friction);
    ObjectTypeDB::bind_method(_MD("set_friction", "friction:real"), &ChipmunkShape::set_friction);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "friction"), _SCS("set_friction"), _SCS("get_friction"));

    ObjectTypeDB::bind_method(_MD("get_surface_velocity:Vector2"), &ChipmunkShape::get_surface_velocity);
    ObjectTypeDB::bind_method(_MD("set_surface_velocity", "velocity:Vector2"), &ChipmunkShape::set_surface_velocity);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "surface_velocity"), _SCS("set_surface_velocity"), _SCS("get_surface_velocity"));

    ObjectTypeDB::bind_method(_MD("get_metadata"), &ChipmunkShape::get_metadata);
    ObjectTypeDB::bind_method(_MD("set_metadata", "metadata:Variant"), &ChipmunkShape::set_metadata);

    ObjectTypeDB::bind_method(_MD("get_collision_type"), &ChipmunkShape::get_collision_type);
    ObjectTypeDB::bind_method(_MD("set_collision_type", "collision_type:int"), &ChipmunkShape::set_collision_type);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "collision_type"), _SCS("set_collision_type"), _SCS("get_collision_type"));

    ObjectTypeDB::bind_method(_MD("get_filter:ChipmunkShapeFilter"), &ChipmunkShape::get_filter);
    ObjectTypeDB::bind_method(_MD("set_filter", "filter:ChipmunkShapeFilter"), &ChipmunkShape::set_filter);
}

ChipmunkShape *ChipmunkShape::get(const cpShape *shape)
{
    auto id = shape ? cpShapeGetUserData(shape) : 0;
    return (ChipmunkShape*)ObjectDB::get_instance(id);
}

// -- Shape Factory

ChipmunkShape *ChipmunkShapeFactory::circle(ChipmunkBody *body, float radius, const Vector2 &offset)
{
    auto *owner = body ? (cpBody*)*body : NULL;
    return wrap(cpCircleShapeNew(owner, radius, CP(offset)));
}

ChipmunkShape *ChipmunkShapeFactory::segment(ChipmunkBody *body, const Vector2 &a, const Vector2 &b, float radius)
{
    auto *owner = body ? (cpBody*)*body : NULL;
    return wrap(cpSegmentShapeNew(owner, CP(a), CP(b), radius));
}

ChipmunkShape *ChipmunkShapeFactory::box(ChipmunkBody *body, const Rect2 &box, float radius)
{
    auto *owner = body ? (cpBody*)*body : NULL;
    return wrap(cpBoxShapeNew2(owner, CP(box), radius));
}

ChipmunkShape *ChipmunkShapeFactory::poly(ChipmunkBody *body, const Vector2Array &verts, float radius)
{
    auto *owner = body ? (cpBody*)*body : NULL;
    Vector2Array::Read r = verts.read();
    auto *cp_verts = reinterpret_cast<const cpVect*>(r.ptr());
    return wrap(cpPolyShapeNewRaw(owner, verts.size(), cp_verts, radius));
}

void ChipmunkShapeFactory::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("circle", "body:ChipmunkBody", "radius:real", "offset:Vector2"), &ChipmunkShapeFactory::circle);
    ObjectTypeDB::bind_method(_MD("segment", "body:ChipmunkBody", "a:Vector2", "b:Vector2", "radius:real"), &ChipmunkShapeFactory::segment);
    ObjectTypeDB::bind_method(_MD("box", "body:ChipmunkBody", "box:Rect2", "radius:real"), &ChipmunkShapeFactory::box);
    ObjectTypeDB::bind_method(_MD("poly", "body:ChipmunkBody", "verts:Vector2Array", "radius:real"), &ChipmunkShapeFactory::poly);
}

ChipmunkShape *ChipmunkShapeFactory::wrap(cpShape *shape)
{
    return memnew(ChipmunkShape(shape));
}
