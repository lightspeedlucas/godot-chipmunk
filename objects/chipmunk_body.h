#ifndef GODOT_CHIPMUNK_BODY_H
#define GODOT_CHIPMUNK_BODY_H

#include "object.h"
#include "chipmunk_common.h"

class ChipmunkBody : public Object
{
    OBJ_TYPE(ChipmunkBody, Object);
public:
    /** Lifecycle */
    ChipmunkBody();
    ChipmunkBody(float, float);
    ~ChipmunkBody();

    /** Chipmunk methods */
    void set_position_update_callback(Object *receiver, const StringName &method);

protected:
    /** Godot bindings */
	static void _bind_methods();
    cpBody *body;

private:
    /** Callbacks */
    ChipmunkCallbackBinding *position_cb;
    static void PositionUpdateFunc(cpBody *body, cpFloat dt);

public:
    /** Chipmunk interoperability */
    operator cpBody*() const { return body; }
    static ChipmunkBody *get(cpBody*);
};

#endif
