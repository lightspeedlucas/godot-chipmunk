#ifndef GODOT_CHIPMUNK_STRUCTS_H
#define GODOT_CHIPMUNK_STRUCTS_H

#include "object.h"
#include "reference.h"

#include "chipmunk/chipmunk.h"

class ChipmunkShapeFilter : public Reference
{
    OBJ_TYPE(ChipmunkShapeFilter, Reference);
protected:
	static void _bind_methods();

public:
    int group;
    int categories;
    int mask;

public:
    void set_group(int p_group);
    int get_group() const;

    void set_categories(int p_categories);
    int get_categories() const;

    void set_mask(int p_mask);
    int get_mask() const;

    ChipmunkShapeFilter();
    ChipmunkShapeFilter(const cpShapeFilter&);

    operator cpShapeFilter() const;
};

#endif
