#ifndef GODOT_CHIPMUNK_COMMON_H
#define GODOT_CHIPMUNK_COMMON_H

#include "object.h"
#include "chipmunk/chipmunk.h"

#include "../chipmunk_structs.h"

class ChipmunkSpace;
class ChipmunkBody;
class ChipmunkShape;

struct ChipmunkCallbackBinding
{
    ObjectID id;
    StringName method;
    
    void call();
    void call(const Variant &arg0);
};

/**********************************************************************/
// Math type conversions

static inline cpVect CP(const Vector2 &v) { return cpv(v.x, v.y); }
static inline cpBB CP(const Rect2 &v) { return cpBBNew(v.pos.x, v.pos.y, v.pos.x + v.size.x, v.pos.y + v.size.y); }

static inline cpTransform CP(const Matrix32 &v)
{
    return cpTransform
    {
        v.elements[0].x, v.elements[0].y,
        v.elements[1].x, v.elements[1].y,
        v.elements[2].x, v.elements[2].y
    };
}

static inline Vector2 GD(const cpVect &v) { return Vector2(v.x, v.y); }
static inline Rect2 GD(const cpBB &v) { return Rect2(v.l, v.b, v.r - v.l, v.t - v.b); }

static inline Matrix32 GD(const cpTransform &v)
{
    return Matrix32(v.a, v.b, v.c, v.d, v.tx, v.ty);
}

/** Enable conversion from Variant to any class derived from Object. */
template<class O>
struct VariantCaster<O*>
{
	static O *cast(const Variant &p_variant)
    {
        auto *obj = (Object*)p_variant;
        return obj ? obj->cast_to<O>() : NULL;
	}
};

#endif