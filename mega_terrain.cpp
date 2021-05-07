

#include "mega_terrain.h"

void mega_terrain::set_clipmap_offset(Vector2 offset) {
    set_offset(offset);
}

Vector3 mega_terrain::intersect_ray(Vector3 from, Vector3 dir, bool refresh = true) {
    from = get_transform().xform_inv(from);
    Plane top = Plane(Vector3(0, 1, 0), get_transform().origin.y + get_size().y);
    Plane bottom = Plane(Vector3(0, 1, 0), get_transform().origin.y);

    Vector3 a, b;

    if (!top.intersects_ray(from, dir, &a))
        a = from;

    if (!bottom.intersects_ray(from, dir, &b))
        b = (dir * 2000.0);

    if (b.distance_squared_to(from) < a.distance_squared_to(from)) {
        Vector3 temp = a;
        a = b;
        b = temp;
    }
 
    return Vector3(0,0,0);
}

