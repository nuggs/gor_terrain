/*
 * Generic Off-Road Terrain System
 * copyright (c) 2021 Anthony Goins
 * the.green.machine@gmail.com
 *
 * Based on Cartographer by Adrien de Pierres <adrien@awkwardpolygons.com>
 */

#ifndef CLIPMAP_H
#define CLIPMAP_H

#include <scene/3d/spatial.h>
#include <scene/3d/camera.h>
#include <core/io/resource_loader.h>
#include <scene/resources/material.h>
#include <scene/resources/mesh.h>
#include <scene/3d/mesh_instance.h>
#include <scene/3d/multimesh_instance.h>
#include <core/math/vector2.h>
#include <core/math/vector3.h>
#include <scene/main/viewport.h>

class clipmap : public Spatial {
    GDCLASS(clipmap, Spatial);

    public:
        int stride;
        bool tracking;
        Ref<ShaderMaterial> shader_material;

        void set_size(Vector3 size);
        void set_offset(Vector2 offset);
        void set_material(Ref<ShaderMaterial> mat);
        void set_layer_mask(int num);
        void set_layer_mask_bit(int layer, bool enabled);
        void set_tracking(bool enable);

        Vector3 get_size(void);
        Vector2 get_offset(void);
        Ref<ShaderMaterial> get_material(void);
        AABB get_aabb(void);
        int get_layer_mask(void);
        int get_layer_mask_bit(int layer);
        bool get_tracking(void);

        void update_bounds(void);
        void update_transforms(void);
        void update_offset(void);

    protected:
        void _init(void);
        void _ready(void);
        void _physics_process(float delta);
        static void _bind_methods(void);

    private:
        Ref<Mesh> center_mesh;
        Ref<Mesh> ring_multimesh;
        MeshInstance *center_mesh_instance;
        MultiMeshInstance *ring_multimesh_instance;

        int layers = 1;
        int ring_parts = 2;
        int ring_base = 2;
        float ring_count;
        float diameter;
        float center_diameter;
        float rings_diameter;
        Vector3 size;
        Vector2 offset;
};

#endif // CLIPMAP_H

