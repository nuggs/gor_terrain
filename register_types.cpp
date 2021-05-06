/*
 * Some type of header here with copyright shit and license and whatever
 */

#include "core/object.h"
#include "register_types.h"
#include "terrain.h"

void register_gor_terrain_types(void) {
    ClassDB::register_class<Terrain>();
}

void unregister_gor_terrain_types(void) {
    // do shit
}

