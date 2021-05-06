/*
 * yeah man
 */

// Use Vector3i once we're able to
#include "core/math/vector3.h"
#include "core/class_db.h"
#include "core/object.h"
#include "register_types.h"
#include "terrain.h"

Terrain::Terrain(void) : friction_func(nullptr) {}

double Terrain::get_height(const Vector3 location) const {
    return 0;
}

Vector3 Terrain::get_normal(const Vector3 location) const {
    return Vector3(0, 0, 1);
}

float Terrain::get_coefficient_friction(const Vector3 location) const {
    return 0.8f;
}

void Terrain::_bind_methods(void) {
    // bind shit here, but we have nothing
}
