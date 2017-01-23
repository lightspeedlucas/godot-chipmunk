#ifndef GODOT_CHIPMUNK_SHAPE_H
#define GODOT_CHIPMUNK_SHAPE_H

#include <object.h>

class ChipmunkShape : public Object
{
    OBJ_TYPE(ChipmunkShape, Object);
protected:
    /** Abstract class */
    ChipmunkShape(cpShape*);
    friend class ChipmunkShapeFactory;

public:
    /** Lifecycle */
    ~ChipmunkShape();

    /** Chipmunk methods */
    Rect2 cache_bb();
    Rect2 update(const Matrix32&);

    Dictionary point_query(const Vector2&) const;

    ChipmunkSpace *get_space() const;
    ChipmunkBody *get_body() const;

    float get_mass() const;
    void set_mass(float);

    float get_density() const;
    void set_density(float);

    bool get_sensor() const;
    void set_sensor(bool);

    float get_elasticity() const;
    void set_elasticity(float);

    float get_friction() const;
    void set_friction(float);

    Variant get_metadata() const;
    void set_metadata(const Variant&);

    int get_collision_type() const;
    void set_collision_type(int);

    Ref<ChipmunkShapeFilter> get_filter() const;
    void set_filter(const Ref<ChipmunkShapeFilter> &filter);

protected:
    /** Godot bindings */
	static void _bind_methods();
    cpShape *shape;
    Variant metadata;

public:
    /** Chipmunk interoperability */
    operator cpShape*() const { return shape; }
    static ChipmunkShape *get(const cpShape*);
};

class ChipmunkShapeFactory : public Reference
{
    OBJ_TYPE(ChipmunkShapeFactory, Reference);
public:
    /** Factory methods */
    ChipmunkShape *circle(ChipmunkBody *body, float radius, const Vector2 &offset);
    ChipmunkShape *segment(ChipmunkBody *body, const Vector2 &a, const Vector2 &b, float radius);
    ChipmunkShape *box(ChipmunkBody *body, const Rect2 &box, float radius);
    ChipmunkShape *poly(ChipmunkBody *body, const Vector2Array &verts, float radius);

protected:
    /** Godot bindings */
	static void _bind_methods();

    /** Wrap Chipmunk object */
    static ChipmunkShape *wrap(cpShape *shape);
};

#endif
