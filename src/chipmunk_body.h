#ifndef GODOT_CHIPMUNK_BODY_H
#define GODOT_CHIPMUNK_BODY_H

#include <object.h>

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

    float get_mass() const;
    void set_mass(float);

    float get_moment() const;
    void set_moment(float);

    Vector2 get_position() const;
    void set_position(const Vector2&);

    Vector2 get_center_of_gravity() const;
    void set_center_of_gravity(const Vector2&);

    Vector2 get_velocity() const;
    void set_velocity(const Vector2&);

    Vector2 get_force() const;
    void set_force(const Vector2&);

    float get_angle() const;
    void set_angle(float);

    float get_angular_velocity() const;
    void set_angular_velocity(float);

    float get_torque() const;
    void set_torque(float);

    Variant get_metadata() const;
    void set_metadata(const Variant&);

    void set_velocity_update_callback(Object *receiver, const StringName &method);
    void set_position_update_callback(Object *receiver, const StringName &method);

    void apply_force_at_world_point(const Vector2 &force, const Vector2 &point);
    void apply_force_at_local_point(const Vector2 &force, const Vector2 &point);

    void apply_impulse_at_world_point(const Vector2 &impulse, const Vector2 &point);
    void apply_impulse_at_local_point(const Vector2 &impulse, const Vector2 &point);

    Vector2 get_velocity_at_world_point(const Vector2 &point);
    Vector2 get_velocity_at_local_point(const Vector2 &point);

    float get_kinetic_energy() const;

protected:
    /** Godot bindings */
	static void _bind_methods();
    cpBody *body;
    Variant metadata;

private:
    /** Callbacks */
    ChipmunkCallbackBinding *velocity_cb;
    static void VelocityUpdateFunc(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt);

    ChipmunkCallbackBinding *position_cb;
    static void PositionUpdateFunc(cpBody *body, cpFloat dt);

public:
    /** Chipmunk interoperability */
    operator cpBody*() const { return body; }
    static ChipmunkBody *get(const cpBody*);
};

#endif
