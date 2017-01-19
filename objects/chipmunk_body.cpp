
#include "chipmunk_body.h"

ChipmunkBody::ChipmunkBody()
    : ChipmunkBody(0, 0)
{
}

ChipmunkBody::ChipmunkBody(float mass, float inertia)
    : ChipmunkBody(cpBodyNew(mass, inertia))
{
}

void ChipmunkBody::destroy()
{
    if (body)
    {
        cpBodyFree(body);
        body = nullptr;
    }
}

void ChipmunkBody::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("destroy"), &ChipmunkBody::destroy);
}
