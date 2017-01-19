
#include "chipmunk_space.h"
#include "chipmunk_body.h"
#include "../chipmunk_server.h"

ChipmunkSpace::ChipmunkSpace()
    : ChipmunkSpace(cpSpaceNew())
{
}

void ChipmunkSpace::destroy()
{
    if (space)
    {
        cpSpaceFree(space);
        space = nullptr;
    }
}

Vector2 ChipmunkSpace::get_gravity() const
{
    ERR_FAIL_NULL_V(space, Vector2());
    return GD(cpSpaceGetGravity(space));
}

void ChipmunkSpace::set_gravity(const Vector2 &v)
{
    ERR_FAIL_NULL(space);
    cpSpaceSetGravity(space, CP(v));
}

void ChipmunkSpace::add_body(const Ref<ChipmunkBody> &body)
{
    ERR_FAIL_NULL(space);
    cpSpaceAddBody(space, **body);
}

void ChipmunkSpace::remove_body(const Ref<ChipmunkBody> &body)
{
    ERR_FAIL_NULL(space);
    cpSpaceRemoveBody(space, **body);
}

void ChipmunkSpace::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("destroy"), &ChipmunkSpace::destroy);

    ObjectTypeDB::bind_method(_MD("get_gravity"), &ChipmunkSpace::get_gravity);
    ObjectTypeDB::bind_method(_MD("set_gravity", "gravity:Vector2"), &ChipmunkSpace::set_gravity);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "gravity"), _SCS("set_gravity"), _SCS("get_gravity"));

    ObjectTypeDB::bind_method(_MD("add_body", "body:ChipmunkBody"), &ChipmunkSpace::add_body);
    ObjectTypeDB::bind_method(_MD("remove_body", "body:ChipmunkBody"), &ChipmunkSpace::remove_body);
}
