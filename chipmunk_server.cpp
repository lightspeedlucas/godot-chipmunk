
#include "chipmunk_server.h"
#include "print_string.h"

ChipmunkServer *ChipmunkServer::singleton = NULL;

RID ChipmunkServer::space_new()
{
    auto *space = cpSpaceNew();
    return space_owner.make_rid(space);
}

void ChipmunkServer::space_free(RID p_rid)
{
    auto *space = space_owner.get(p_rid);
    space_owner.free(p_rid);
    cpSpaceFree(space);
}

Vector2 ChipmunkServer::get_space_gravity(RID p_rid)
{
    auto *space = space_owner.get(p_rid);
    return GDV(cpSpaceGetGravity(space));
}

void ChipmunkServer::set_space_gravity(RID p_rid, Vector2 p_gravity)
{
    auto *space = space_owner.get(p_rid);
    cpSpaceSetGravity(space, CPV(p_gravity));
}

float ChipmunkServer::get_space_damping(RID p_rid)
{
    auto *space = space_owner.get(p_rid);
    return cpSpaceGetDamping(space);
}

void ChipmunkServer::set_space_damping(RID p_rid, float p_damping)
{
    auto *space = space_owner.get(p_rid);
    cpSpaceSetDamping(space, p_damping);
}

float ChipmunkServer::get_space_idle_speed_threshold(RID p_rid)
{
    auto *space = space_owner.get(p_rid);
    return cpSpaceGetIdleSpeedThreshold(space);
}

void ChipmunkServer::set_space_idle_speed_threshold(RID p_rid, float p_threshold)
{
    auto *space = space_owner.get(p_rid);
    cpSpaceSetIdleSpeedThreshold(space, p_threshold);
}

float ChipmunkServer::get_space_sleep_time_threshold(RID p_rid)
{
    auto *space = space_owner.get(p_rid);
    return cpSpaceGetSleepTimeThreshold(space);
}

void ChipmunkServer::set_space_sleep_time_threshold(RID p_rid, float p_threshold)
{
    auto *space = space_owner.get(p_rid);
    cpSpaceSetSleepTimeThreshold(space, p_threshold);
}

void ChipmunkServer::space_step(RID p_rid, float p_dt)
{
    auto *space = space_owner.get(p_rid);
    cpSpaceStep(space, p_dt);
}

void ChipmunkServer::_bind_methods()
{
    /** Space */
    ObjectTypeDB::bind_method(_MD("space_new"), &ChipmunkServer::space_new);
    ObjectTypeDB::bind_method(_MD("space_free", "rid"), &ChipmunkServer::space_free);
    ObjectTypeDB::bind_method(_MD("get_space_gravity", "rid"), &ChipmunkServer::get_space_gravity);
    ObjectTypeDB::bind_method(_MD("set_space_gravity", "rid", "gravity"), &ChipmunkServer::set_space_gravity);
    ObjectTypeDB::bind_method(_MD("get_space_damping", "rid"), &ChipmunkServer::get_space_damping);
    ObjectTypeDB::bind_method(_MD("set_space_damping", "rid", "damping"), &ChipmunkServer::set_space_damping);
    ObjectTypeDB::bind_method(_MD("get_space_idle_speed_threshold", "rid"), &ChipmunkServer::get_space_idle_speed_threshold);
    ObjectTypeDB::bind_method(_MD("set_space_idle_speed_threshold", "rid", "threshold"), &ChipmunkServer::set_space_idle_speed_threshold);
    ObjectTypeDB::bind_method(_MD("get_space_sleep_time_threshold", "rid"), &ChipmunkServer::get_space_sleep_time_threshold);
    ObjectTypeDB::bind_method(_MD("set_space_sleep_time_threshold", "rid", "threshold"), &ChipmunkServer::set_space_sleep_time_threshold);
    ObjectTypeDB::bind_method(_MD("space_step", "rid", "dt"), &ChipmunkServer::space_step);
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
