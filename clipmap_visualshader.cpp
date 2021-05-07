/*
 * Generic Off-Road Terrain System
 * copyright (c) 2021 Anthony Goins
 * the.green.machine@gmail.com
 *
 * Based on Cartographer by Adrien de Pierres <adrien@awkwardpolygons.com>
 */

#include "clipmap_visualshader.h"

void clipmap_visual_shader::_init(void) {
    set("flags/skip_vertex_transform", true);
    vertex_node = memnew(vs_clipmap_vertex);
    transform_node = memnew(vs_clipmap_transform);
    tangent_space_node = memnew(vs_tangent_space);
    heightmap_calc_node = memnew(vs_heightmap_calc);
    offset_add_node = memnew(VisualShaderNodeVectorOp);
    offset_add_node->set_operator(VisualShaderNodeVectorOp::OP_ADD);

    add_node(TYPE_VERTEX, transform_node, Vector2(32, 32), 3);
    add_node(TYPE_VERTEX, tangent_space_node, Vector2(-256, -64), 4);
    add_node(TYPE_VERTEX, heightmap_calc_node, Vector2(-512, -48), 5);
    add_node(TYPE_VERTEX, offset_add_node, Vector2(-256, 64), 6);
    add_node(TYPE_VERTEX, vertex_node, Vector2(-768, 32), 7);
    connect_nodes(TYPE_VERTEX, 4, 0, 3, 1);
}

