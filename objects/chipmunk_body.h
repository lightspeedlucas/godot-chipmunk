#ifndef GODOT_CHIPMUNK_BODY_H
#define GODOT_CHIPMUNK_BODY_H

#include "object.h"
#include "reference.h"

#include "chipmunk/chipmunk.h"

class ChipmunkBody : public Reference
{
    OBJ_TYPE(ChipmunkBody, Reference);
public:
    ChipmunkBody();
    ChipmunkBody(float, float);

    void destroy();

protected:
	static void _bind_methods();

    cpBody *body;

public:
    explicit ChipmunkBody(cpBody *body) : body(body) {}
    operator cpBody*() const { return body; }
};

#endif
