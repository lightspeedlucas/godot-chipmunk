
#include "chipmunk_common.h"

void ChipmunkCallbackBinding::call()
{
    if (auto *obj = ObjectDB::get_instance(id))
    {
        Variant::CallError ce;
        obj->call(method, NULL, 0, ce);
    }
}

void ChipmunkCallbackBinding::call(const Variant &arg0)
{
    if (auto *obj = ObjectDB::get_instance(id))
    {
        const Variant *vp[] = { &arg0 };
        Variant::CallError ce;
        obj->call(method, vp, 1, ce);
    }
}
