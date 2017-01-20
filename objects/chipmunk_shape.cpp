
#include "chipmunk_shape.h"
#include "chipmunk_body.h"
#include "chipmunk_space.h"

ChipmunkShape::ChipmunkShape(cpShape *shape)
    : shape(shape)
{
    cpShapeSetUserData(shape, get_instance_ID());
}

ChipmunkShape::~ChipmunkShape()
{
    cpShapeFree(shape);
}

float ChipmunkShape::get_density() const
{
    return cpShapeGetDensity(shape);
}

void ChipmunkShape::set_density(float value)
{
    cpShapeSetDensity(shape, value);
}

ChipmunkSpace *ChipmunkShape::get_space() const
{
    return ChipmunkSpace::get(cpShapeGetSpace(shape));
}

void ChipmunkShape::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("get_density"), &ChipmunkShape::get_density);
    ObjectTypeDB::bind_method(_MD("set_density", "density:real"), &ChipmunkShape::set_density);
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "density"), _SCS("set_density"), _SCS("get_density"));

    ObjectTypeDB::bind_method(_MD("get_space"), &ChipmunkShape::get_space);
}

ChipmunkShape *ChipmunkShape::get(cpShape *shape)
{
    auto id = shape ? cpShapeGetUserData(shape) : 0;
    return (ChipmunkShape*)ObjectDB::get_instance(id);
}

// -- Shape Factory

ChipmunkShape *ChipmunkShapeFactory::circle(ChipmunkBody *body, float radius, const Vector2 &offset)
{
    return wrap(cpCircleShapeNew(*body, radius, CP(offset)));
}

ChipmunkShape *ChipmunkShapeFactory::segment(ChipmunkBody *body, const Vector2 &a, const Vector2 &b, float radius)
{
    return wrap(cpSegmentShapeNew(*body, CP(a), CP(b), radius));
}

ChipmunkShape *ChipmunkShapeFactory::box(ChipmunkBody *body, const Rect2 &box, float radius)
{
    return wrap(cpBoxShapeNew2(*body, CP(box), radius));
}

ChipmunkShape *ChipmunkShapeFactory::poly(ChipmunkBody *body, const Vector2Array &verts, float radius)
{
    Vector2Array::Read r = verts.read();
    auto *cp_verts = reinterpret_cast<const cpVect*>(r.ptr());
    return wrap(cpPolyShapeNewRaw(*body, verts.size(), cp_verts, radius));
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
