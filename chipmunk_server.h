#ifndef GODOT_CHIPMUNK_SERVER_H
#define GODOT_CHIPMUNK_SERVER_H

#include "object.h"
#include "reference.h"

#include "chipmunk/chipmunk.h"
#include "chipmunk_structs.h"

class ChipmunkServer : public Object
{
    OBJ_TYPE(ChipmunkServer, Object);

    static ChipmunkServer *singleton;

protected:
    static void _bind_methods();

    mutable RID_Owner<cpSpace> space_owner;
    mutable RID_Owner<cpBody> body_owner;
    mutable RID_Owner<cpShape> shape_owner;
    mutable RID_Owner<cpConstraint> constraint_owner;

    struct GodotData
    {
		RID rid;
		Variant metadata;
        GodotData() {}
        GodotData(RID p_rid) : rid(p_rid) {}
	};

    List<GodotData> data_pool;
    typedef List<GodotData>::Element GodotDataRef;

public:
    static ChipmunkServer *get_singleton();

    /** Space */
    RID space_new();
    void space_free(RID p_space);
    int space_get_iterations(RID p_space);
    void space_set_iterations(RID p_space, int p_iterations);
    Vector2 space_get_gravity(RID p_space);
    void space_set_gravity(RID p_space, Vector2 p_gravity);
    float space_get_damping(RID p_space);
    void space_set_damping(RID p_space, float p_damping);
    float space_get_idle_speed_threshold(RID p_space);
    void space_set_idle_speed_threshold(RID p_space, float p_idleSpeedThreshold);
    float space_get_sleep_time_threshold(RID p_space);
    void space_set_sleep_time_threshold(RID p_space, float p_sleepTimeThreshold);
    float space_get_collision_slop(RID p_space);
    void space_set_collision_slop(RID p_space, float p_collisionSlop);
    float space_get_collision_bias(RID p_space);
    void space_set_collision_bias(RID p_space, float p_collisionBias);
    int space_get_collision_persistence(RID p_space);
    void space_set_collision_persistence(RID p_space, int p_collisionPersistence);
    float space_get_current_time_step(RID p_space);
    bool space_is_locked(RID p_space);
    RID space_add_shape(RID p_space, RID p_shape);
    RID space_add_body(RID p_space, RID p_body);
    RID space_add_constraint(RID p_space, RID p_constraint);
    void space_remove_shape(RID p_space, RID p_shape);
    void space_remove_body(RID p_space, RID p_body);
    void space_remove_constraint(RID p_space, RID p_constraint);
    bool space_contains_shape(RID p_space, RID p_shape);
    bool space_contains_body(RID p_space, RID p_body);
    bool space_contains_constraint(RID p_space, RID p_constraint);
    void space_reindex_static(RID p_space);
    void space_reindex_shape(RID p_space, RID p_shape);
    void space_reindex_shapes_for_body(RID p_space, RID p_body);
    void space_use_spatial_hash(RID p_space, float p_dim, int p_count);
    void space_step(RID p_space, float p_dt);

    Dictionary space_point_query_nearest(RID p_space, Vector2 p_point, float p_maxDistance, const Ref<ChipmunkShapeFilter> &p_filter);

    /** Body */
    RID body_new(float p_mass, float p_moment);
    RID body_new_kinematic();
    RID body_new_static();
    void body_free(RID p_body);
    void body_activate(RID p_body);
    void body_activate_static(RID p_body, RID p_filter);
    void body_sleep(RID p_body);
    void body_sleep_with_group(RID p_body, RID p_group);
    bool body_is_sleeping(RID p_body);
    int body_get_type(RID p_body);
    void body_set_type(RID p_body, int p_type);
    RID body_get_space(RID p_body);
    float body_get_mass(RID p_body);
    void body_set_mass(RID p_body, float p_m);
    float body_get_moment(RID p_body);
    void body_set_moment(RID p_body, float p_i);
    Vector2 body_get_position(RID p_body);
    void body_set_position(RID p_body, Vector2 p_pos);
    Vector2 body_get_center_of_gravity(RID p_body);
    void body_set_center_of_gravity(RID p_body, Vector2 p_cog);
    Vector2 body_get_velocity(RID p_body);
    void body_set_velocity(RID p_body, Vector2 p_velocity);
    Vector2 body_get_force(RID p_body);
    void body_set_force(RID p_body, Vector2 p_force);
    float body_get_angle(RID p_body);
    void body_set_angle(RID p_body, float p_a);
    float body_get_angular_velocity(RID p_body);
    void body_set_angular_velocity(RID p_body, float p_angularVelocity);
    float body_get_torque(RID p_body);
    void body_set_torque(RID p_body, float p_torque);
    Vector2 body_get_rotation(RID p_body);
    void body_update_velocity(RID p_body, Vector2 p_gravity, float p_damping, float p_dt);
    void body_update_position(RID p_body, float p_dt);
    Vector2 body_local_to_world(RID p_body, Vector2 p_point);
    Vector2 body_world_to_local(RID p_body, Vector2 p_point);
    void body_apply_force_at_world_point(RID p_body, Vector2 p_force, Vector2 p_point);
    void body_apply_force_at_local_point(RID p_body, Vector2 p_force, Vector2 p_point);
    void body_apply_impulse_at_world_point(RID p_body, Vector2 p_impulse, Vector2 p_point);
    void body_apply_impulse_at_local_point(RID p_body, Vector2 p_impulse, Vector2 p_point);
    Vector2 body_get_velocity_at_world_point(RID p_body, Vector2 p_point);
    Vector2 body_get_velocity_at_local_point(RID p_body, Vector2 p_point);
    float body_kinetic_energy(RID p_body);

    /** Shape */
    void shape_free(RID p_shape);
    Rect2 shape_cache_bb(RID p_shape);
    Rect2 shape_update(RID p_shape, Matrix32 p_transform);
    RID shape_get_space(RID p_shape);
    RID shape_get_body(RID p_shape);
    void shape_set_body(RID p_shape, RID p_body);
    float shape_get_mass(RID p_shape);
    void shape_set_mass(RID p_shape, float p_mass);
    float shape_get_density(RID p_shape);
    void shape_set_density(RID p_shape, float p_density);
    float shape_get_moment(RID p_shape);
    float shape_get_area(RID p_shape);
    Vector2 shape_get_center_of_gravity(RID p_shape);
    Rect2 shape_get_bb(RID p_shape);
    bool shape_get_sensor(RID p_shape);
    void shape_set_sensor(RID p_shape, bool p_sensor);
    float shape_get_elasticity(RID p_shape);
    void shape_set_elasticity(RID p_shape, float p_elasticity);
    float shape_get_friction(RID p_shape);
    void shape_set_friction(RID p_shape, float p_friction);
    Vector2 shape_get_surface_velocity(RID p_shape);
    void shape_set_surface_velocity(RID p_shape, Vector2 p_surfaceVelocity);
    int shape_get_collision_type(RID p_shape);
    void shape_set_collision_type(RID p_shape, int p_collisionType);
    RID circle_shape_new(RID p_body, float p_radius, Vector2 p_offset);
    Vector2 circle_shape_get_offset(RID p_shape);
    float circle_shape_get_radius(RID p_shape);
    RID segment_shape_new(RID p_body, Vector2 p_a, Vector2 p_b, float p_radius);
    void segment_shape_set_neighbors(RID p_shape, Vector2 p_prev, Vector2 p_next);
    Vector2 segment_shape_get_a(RID p_shape);
    Vector2 segment_shape_get_b(RID p_shape);
    Vector2 segment_shape_get_normal(RID p_shape);
    float segment_shape_get_radius(RID p_shape);

    /** PolyShape */
    RID poly_shape_new(RID p_body, const Vector2Array &p_verts, Matrix32 p_transform, float p_radius);
    RID poly_shape_new_raw(RID p_body, const Vector2Array &p_verts, float p_radius);
    RID box_shape_new(RID p_body, float p_width, float p_height, float p_radius);
    RID box_shape_new2(RID p_body, Rect2 p_box, float p_radius);
    int poly_shape_get_count(RID p_shape);
    Vector2 poly_shape_get_vert(RID p_shape, int p_index);
    float poly_shape_get_radius(RID p_shape);

    /** Constraint */
    void constraint_free(RID p_constraint);
    RID constraint_get_space(RID p_constraint);
    RID constraint_get_body_a(RID p_constraint);
    RID constraint_get_body_b(RID p_constraint);
    float constraint_get_max_force(RID p_constraint);
    void constraint_set_max_force(RID p_constraint, float p_maxForce);
    float constraint_get_error_bias(RID p_constraint);
    void constraint_set_error_bias(RID p_constraint, float p_errorBias);
    float constraint_get_max_bias(RID p_constraint);
    void constraint_set_max_bias(RID p_constraint, float p_maxBias);
    bool constraint_get_collide_bodies(RID p_constraint);
    void constraint_set_collide_bodies(RID p_constraint, bool p_collideBodies);
    float constraint_get_impulse(RID p_constraint);

    /** Pin Joint */
    bool constraint_is_pin_joint(RID p_constraint);
    RID pin_joint_new(RID p_a, RID p_b, Vector2 p_anchorA, Vector2 p_anchorB);
    Vector2 pin_joint_get_anchor_a(RID p_constraint);
    void pin_joint_set_anchor_a(RID p_constraint, Vector2 p_anchorA);
    Vector2 pin_joint_get_anchor_b(RID p_constraint);
    void pin_joint_set_anchor_b(RID p_constraint, Vector2 p_anchorB);
    float pin_joint_get_dist(RID p_constraint);
    void pin_joint_set_dist(RID p_constraint, float p_dist);

    ChipmunkServer();
	~ChipmunkServer();
};

#endif
