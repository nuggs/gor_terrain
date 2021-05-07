
#ifndef MEGA_TERRAIN_H
#define MEGA_TERRAIN_H

#include "clipmap.h"

class mega_terrain : public clipmap {
    GDCLASS(mega_terrain, clipmap);

    public:
        void set_clipmap_offset(Vector2 offset);
        Vector3 intersect_ray(Vector3 from, Vector3 dir, bool refresh);
};
#endif // MEGA_TERRAIN_H
