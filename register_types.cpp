/* register_types.cpp */

#include "register_types.h"
#include "object_type_db.h"
#include "print_string.h"

#include "chipmunk/chipmunk.h"
#include "chipmunk_server.h"

void register_chipmunk_types()
{
    print_line(String("Chipmunk version: ") + String(cpVersionString));
    ObjectTypeDB::register_type<ChipmunkServer>();
}

void unregister_chipmunk_types()
{
}