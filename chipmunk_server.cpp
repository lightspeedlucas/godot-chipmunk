
#include "chipmunk_server.h"
#include "print_string.h"

ChipmunkServer *ChipmunkServer::singleton = NULL;

RID ChipmunkServer::space_new()
{
    auto *space = cpSpaceNew();
    RID id = space_owner.make_rid(space);
    return id;
}

void ChipmunkServer::_bind_methods()
{
    ObjectTypeDB::bind_method(_MD("space_new"), &ChipmunkServer::space_new);
}

ChipmunkServer *ChipmunkServer::get_singleton()
{
    return singleton;
}

ChipmunkServer::ChipmunkServer()
{
    singleton = this;
}

ChipmunkServer::~ChipmunkServer()
{
    singleton = NULL;
}
