/*
 * copyright shit
 */

#ifndef TERRAIN_H
#define TERRAIN_H

//#include "core/object.h"

/* Using object right now, may change i don't know */
class Terrain : public Object {
    GDCLASS(Terrain, Object);

    public:
        Terrain(void);
        virtual ~Terrain(void) {}
        virtual void synchronize(double time) {}
        virtual void advance(double step) {}
        virtual double get_height(const Vector3 location) const;
        virtual Vector3 get_normal(const Vector3 location) const;
        virtual float get_coefficient_friction(const Vector3 location) const;

        class friction_functor {
            public:
                virtual ~friction_functor(void) {}
                virtual float operator()(const Vector3 location) = 0;
        };

        void register_friction_functor(friction_functor *functor) { friction_func = functor; }

    protected:
        friction_functor *friction_func;
        static void _bind_methods(void);
};

#endif // TERRAIN_H
