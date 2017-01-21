#ifndef GODOT_CHIPMUNK_COLLISION_HANDLER_H
#define GODOT_CHIPMUNK_COLLISION_HANDLER_H

#include <godot_chipmunk.h>

class ChipmunkCollisionHandler : public Object
{
    OBJ_TYPE(ChipmunkCollisionHandler, Object);
private:
    /** Lifecycle */
    ChipmunkCollisionHandler(ChipmunkSpace*, cpCollisionHandler*);
    static ChipmunkCollisionHandler *get(cpSpace*, cpDataPointer);

public:
    /** Lifecycle */
    static ChipmunkCollisionHandler *get_or_create(ChipmunkSpace*, cpCollisionHandler*);
    ~ChipmunkCollisionHandler();

    /** Property getters/setters */
    ChipmunkSpace *get_space() const;
    int get_collision_type_a() const;
    int get_collision_type_b() const;

    void set_begin_func(Object *receiver, const StringName &method);
    void set_pre_solve_func(Object *receiver, const StringName &method);
    void set_post_solve_func(Object *receiver, const StringName &method);
    void set_separate_func(Object *receiver, const StringName &method);

protected:
    /** Godot bindings */
	static void _bind_methods();
    cpCollisionHandler default_handler;
    cpCollisionHandler *handler;
    ChipmunkSpace *space;

private:
    /** Callbacks */
    ChipmunkCallbackBinding *begin_cb;
    static bool BeginFunc(cpArbiter *arb, cpSpace *space, cpDataPointer userData);

    ChipmunkCallbackBinding *pre_solve_cb;
    static bool PreSolveFunc(cpArbiter *arb, cpSpace *space, cpDataPointer userData);

    ChipmunkCallbackBinding *post_solve_cb;
    static void PostSolveFunc(cpArbiter *arb, cpSpace *space, cpDataPointer userData);

    ChipmunkCallbackBinding *separate_cb;
    static void SeparateFunc(cpArbiter *arb, cpSpace *space, cpDataPointer userData);
};

#endif
