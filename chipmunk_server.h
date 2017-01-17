#ifndef CHIPMUNK_SERVER_H
#define CHIPMUNK_SERVER_H

#include "object.h"
#include "reference.h"

#include "chipmunk/chipmunk.h"

class ChipmunkServer : public Object
{
    OBJ_TYPE(ChipmunkServer, Object);

    static ChipmunkServer *singleton;

protected:
    static void _bind_methods();

    mutable RID_Owner<cpSpace> space_owner;

public:
    static ChipmunkServer *get_singleton();

    RID space_new();
}

#endif
