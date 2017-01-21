#ifndef GODOT_CHIPMUNK_STRUCTS_H
#define GODOT_CHIPMUNK_STRUCTS_H

#include "object.h"
#include "reference.h"

#include "chipmunk/chipmunk.h"

class ChipmunkShapeFilter : public Reference
{
    OBJ_TYPE(ChipmunkShapeFilter, Reference);
public:
    /** Lifecycle */
    ChipmunkShapeFilter();

public:
    /** Chipmunk properties */
    int group;
    int categories;
    int mask;

public:
    /** Properties setters/getters */
    void set_group(int p_group);
    int get_group() const;

    void set_categories(int p_categories);
    int get_categories() const;

    void set_mask(int p_mask);
    int get_mask() const;

protected:
    /** Godot bindings */
	static void _bind_methods();

public:
    /** Chipmunk interoperability */
    operator cpShapeFilter() const;
    ChipmunkShapeFilter(const cpShapeFilter&);
};

#endif
