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
    ~ChipmunkBody();

    /** Chipmunk methods */
    void activate();
    void sleep();
    bool is_sleeping() const;

    int get_body_type() const;
    void set_body_type(int);
    
    ChipmunkSpace *get_space() const;

    Vector2 get_position() const;
    void set_position(const Vector2&);

    float get_angle() const;
    void set_angle(float);

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
