
#include "chipmunk_space.h"
#include "chipmunk_body.h"
#include "chipmunk_shape.h"

ChipmunkSpace::ChipmunkSpace()
{
    space = cpSpaceNew();
    cpSpaceSetUserData(space, get_instance_ID());
}

ChipmunkSpace::~ChipmunkSpace()
{
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

void ChipmunkSpace::add_body(ChipmunkBody *body)
{
    cpSpaceAddBody(space, *body);
}

void ChipmunkSpace::remove_body(ChipmunkBody *body)
{
    cpSpaceRemoveBody(space, *body);
}

void ChipmunkSpace::add_shape(ChipmunkShape *shape)
{
    cpSpaceAddShape(space, *shape);
}

void ChipmunkSpace::remove_shape(ChipmunkShape *shape)
{
    cpSpaceRemoveShape(space, *shape);
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

    ObjectTypeDB::bind_method(_MD("add_body", "body:ChipmunkBody"), &ChipmunkSpace::add_body);
    ObjectTypeDB::bind_method(_MD("remove_body", "body:ChipmunkBody"), &ChipmunkSpace::remove_body);

    ObjectTypeDB::bind_method(_MD("add_shape", "shape:ChipmunkShape"), &ChipmunkSpace::add_shape);
    ObjectTypeDB::bind_method(_MD("remove_shape", "shape:ChipmunkShape"), &ChipmunkSpace::remove_shape);

    ObjectTypeDB::bind_method(_MD("step", "dt:real"), &ChipmunkSpace::step);
}

ChipmunkSpace *ChipmunkSpace::get(cpSpace *space)
{
    auto id = space ? cpSpaceGetUserData(space) : 0;
    return (ChipmunkSpace*)ObjectDB::get_instance(id);
}
