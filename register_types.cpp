/* register_types.cpp */

#include "register_types.h"
#include "object_type_db.h"
#include "globals.h"
#include "print_string.h"

#include "godot_chipmunk.h"

void register_chipmunk_types()
{
    print_line(String("Chipmunk version: ") + String(cpVersionString));

    // initialize server
    //memnew(ChipmunkServer);

    // register auxiliary types
    ObjectTypeDB::register_type<ChipmunkSpace>();
    ObjectTypeDB::register_type<ChipmunkBody>();
    ObjectTypeDB::register_virtual_type<ChipmunkShape>();
    ObjectTypeDB::register_virtual_type<ChipmunkConstraint>();

    ObjectTypeDB::register_virtual_type<ChipmunkPinJoint>();

    ObjectTypeDB::register_type<ChipmunkShapeFactory>();
    ObjectTypeDB::register_type<ChipmunkConstraintFactory>();

    ObjectTypeDB::register_virtual_type<ChipmunkCollisionHandler>();
    ObjectTypeDB::register_type<ChipmunkShapeFilter>();

    // register server
    //Globals::get_singleton()->add_singleton(Globals::Singleton("ChipmunkServer", ChipmunkServer::get_singleton()));
}

void unregister_chipmunk_types()
{
    // destroy server
    //memdelete(ChipmunkServer::get_singleton());
}