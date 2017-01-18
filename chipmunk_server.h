#ifndef CHIPMUNK_SERVER_H
#define CHIPMUNK_SERVER_H

#include "object.h"
#include "reference.h"

#include "chipmunk/chipmunk.h"

inline cpVect CPV(const Vector2 &vec) { return cpv(vec.x, vec.y); }
inline Vector2 GDV(const cpVect &vec) { return Vector2(vec.x, vec.y); }

class ChipmunkServer : public Object
{
    OBJ_TYPE(ChipmunkServer, Object);

    static ChipmunkServer *singleton;

protected:
    static void _bind_methods();

    mutable RID_Owner<cpSpace> space_owner;

public:
    static ChipmunkServer *get_singleton();

    /** Space */
    RID space_new();
    void space_free(RID p_rid);
    Vector2 get_space_gravity(RID p_rid);
    void set_space_gravity(RID p_rid, Vector2 p_gravity);
    float get_space_damping(RID p_rid);
    void set_space_damping(RID p_rid, float p_damping);
    float get_space_idle_speed_threshold(RID p_rid);
    void set_space_idle_speed_threshold(RID p_rid, float p_threshold);
    float get_space_sleep_time_threshold(RID p_rid);
    void set_space_sleep_time_threshold(RID p_rid, float p_threshold);
    void space_step(RID p_rid, float p_dt);

    ChipmunkServer();
	~ChipmunkServer();
};

#endif
