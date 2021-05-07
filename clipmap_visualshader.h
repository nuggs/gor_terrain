/*
 * Generic Off-Road Terrain System
 * copyright (c) 2021 Anthony Goins
 * the.green.machine@gmail.com
 *
 * Based on Cartographer by Adrien de Pierres <adrien@awkwardpolygons.com>
 */

#ifndef CLIPMAP_VISUALSHADER_H
#define CLIPMAP_VISUALSHADER_H

#include <scene/resources/shader.h>
#include <scene/resources/visual_shader.h>
#include <scene/resources/visual_shader_nodes.h>
#include "shaders/clipmap_transform.h"
#include "shaders/clipmap_vertex.h"
#include "shaders/heightmap_calc.h"
#include "shaders/tangent_space.h"

class clipmap_visual_shader : public VisualShader {
    GDCLASS(clipmap_visual_shader, VisualShader)

    public:
        vs_clipmap_vertex *vertex_node;
        vs_clipmap_transform *transform_node;
        vs_tangent_space *tangent_space_node;
        vs_heightmap_calc *heightmap_calc_node;
        VisualShaderNodeVectorOp *offset_add_node;

    protected:
        void _init(void);
};

#endif // CLIPMAP_VISUALSHADER_H

