/*
 * Generic Off-Road Terrain System
 * copyright (c) 2021 Anthony Goins
 * the.green.machine@gmail.com
 *
 * Based on Cartographer by Adrien de Pierres <adrien@awkwardpolygons.com>
 */

#include "clipmap.h"

void clipmap::set_layer_mask(int layer_mask) {
    layers = layer_mask;
    if (center_mesh_instance != nullptr)
        center_mesh_instance->set_layer_mask(layers);

    if (ring_multimesh_instance != nullptr)
        ring_multimesh_instance->set_layer_mask(layers);
}

int clipmap::get_layer_mask(void) {
    return layers;
}

void clipmap::set_layer_mask_bit(int layer, bool enabled) {
    int b = 1 << layer;
    int v = 0;

    if (enabled == true) 
        v = layers | b;
    else
        v = layers & ~b;
    set_layer_mask(v);
}

int clipmap::get_layer_mask_bit(int layer) {
    return layers & (1 << layer);
}

Vector3 clipmap::get_size(void) {
    return size;
}

void clipmap::set_size(Vector3 new_size) {
    size = new_size;
    update_bounds();
    update_transforms();
}

Vector2 clipmap::get_offset(void) {
    return offset;
}

void clipmap::set_offset(Vector2 new_offset) {
    offset = new_offset;

    Vector3 updated_offset = Vector3(new_offset.x, 0.0, new_offset.y);

    // We may need to use set_global_transform instead, need testing
    Transform center_transform = center_mesh_instance->get_transform();
    center_transform.origin = updated_offset;
    center_mesh_instance->set_transform(center_transform);

    Transform ring_transform = ring_multimesh_instance->get_transform();
    ring_transform.origin = updated_offset;
    ring_multimesh_instance->set_transform(ring_transform);

    if (get_material() != nullptr)
        shader_material->set_shader_param("origin", updated_offset);
}

Ref<ShaderMaterial> clipmap::get_material(void) {
    if (shader_material != nullptr)
        return shader_material;

    return nullptr;
}

void clipmap::set_material(Ref<ShaderMaterial> mat) {
    shader_material = mat;
    center_mesh_instance->set_material_override(mat);
    ring_multimesh_instance->set_material_override(mat);
}

void clipmap::set_tracking(bool enabled) {
    tracking = enabled;
    set_physics_process(enabled);
}

bool clipmap::get_tracking(void) {
    return tracking;
}

void clipmap::_init(void) {
    center_mesh = ResourceLoader::load("mesh/center_quad.obj", "Mesh");
    center_mesh_instance = memnew(MeshInstance);
    center_mesh_instance->set_mesh(center_mesh);

    ring_multimesh = ResourceLoader::load("mesh/ring_base2_quad2.obj", "MultiMesh");
    ring_multimesh_instance = memnew(MultiMeshInstance);
    ring_multimesh_instance->set_multimesh(ring_multimesh);

    add_child(center_mesh_instance);
    add_child(ring_multimesh_instance);
    set_physics_process(get_tracking());
}

void clipmap::_physics_process(float delta) {
    update_offset();
}

void clipmap::_ready(void) {
    set_size(size);
}

void clipmap::update_bounds(void) {
    Vector3 center_size = center_mesh->get_aabb().size;

    center_diameter = std::max(center_size.x, center_size.z);
    diameter = std::max(size.x, size.z);
    ring_count = ceil(log(diameter / center_diameter) / log(ring_base));
    rings_diameter = pow(ring_base, ring_count) * center_diameter;
    ring_multimesh_instance->get_multimesh()->set_instance_count(ring_count * ring_parts);

    AABB center_aabb = center_mesh->get_aabb();
    center_aabb.size.y = size.y;
    // Apparently, this is how we set AABB on meshes.
    center_mesh->get_aabb().set_position(center_aabb.position);
    center_mesh->get_aabb().set_size(center_aabb.size);
    AABB ring_aabb = AABB(-Vector3(rings_diameter/2.0, 0, rings_diameter/2.0), Vector3(rings_diameter, size.y, rings_diameter));
    ring_multimesh_instance->set_custom_aabb(ring_aabb);
}

void clipmap::update_transforms(void) {
    for (int idx = 0; idx <= ring_multimesh_instance->get_multimesh()->get_instance_count(); idx++) {
        float lvl = float(int(idx) / ring_parts);
        float mul = pow(ring_base, lvl);
        if (int(idx) % ring_parts == 0)
            mul = mul;
        else
            mul = -mul;
        Transform trn = Transform(mul, 0, 0, 0, 1, 0, 0, 0, mul, 0, 0, 0);
        ring_multimesh_instance->get_multimesh()->set_instance_transform(idx, trn);
    }
}

void clipmap::update_offset(void) {
    const Viewport *viewport = get_viewport();
    const Camera *camera = viewport->get_camera();
    Vector3 offset3 = camera->get_camera_transform().origin;
    offset3 = (offset3 / stride).floor() * stride;
    Vector2 offset2 = Vector2(offset3.x, offset3.z);

    if (offset2 != offset)
        set_offset(offset2);
}

AABB clipmap::get_aabb(void) {
    return ring_multimesh_instance->get_aabb();
}

