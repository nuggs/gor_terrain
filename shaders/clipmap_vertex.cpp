/*
 * Generic Off-Road Terrain System
 * copyright (c) 2021 Anthony Goins
 * the.green.machine@gmail.com
 *
 * Based on Cartographer by Adrien de Pierres <adrien@awkwardpolygons.com>
 */

#include "clipmap_vertex.h"

const String vs_clipmap_vertex::_get_name(void) {
    return "clipmap_vertex";
}

String vs_clipmap_vertex::_get_category(void) {
    return "gor_terrain";
}

const String vs_clipmap_vertex::_get_description(void) {
    return "Clipmap vertex transform node";
}

const int vs_clipmap_vertex::_get_input_port_count(void) {
    return 0;
}

const String vs_clipmap_vertex::_get_input_port_name(int port) {
    return "";
}

const VisualShaderNodeCustom::PortType vs_clipmap_vertex::_get_input_port_type(int port) {
    return PORT_TYPE_MAX;
}

const int vs_clipmap_vertex::_get_output_port_count(void) {
    return 5;
}

const String vs_clipmap_vertex::_get_output_port_name(int port) {
    switch (port) {
        case 0: return "size";
        case 1: return "diameter";
        case 2: return "vertex";
        case 3: return "uv";
        case 4: return "uv2";
    }
    return "size";
}

const VisualShaderNodeCustom::PortType vs_clipmap_vertex::_get_output_port_type(int port) {
    switch (port) {
        case 0: return PORT_TYPE_VECTOR;
        case 1: return PORT_TYPE_SCALAR;
        case 2: return PORT_TYPE_VECTOR;
        case 3: return PORT_TYPE_VECTOR;
        case 4: return PORT_TYPE_VECTOR;
    }
    return PORT_TYPE_VECTOR;
}

const String vs_clipmap_vertex::_get_global_code(VisualShaderNodeCustom::PortType mode) {
    return "// clipmap globals"
            "const float MESH_SIZE= 128.0;"
            "const float MESH_STRIDE = 81.0;"
            "uniform int INSTANCE_COUNT = 1;"
            "uniform vec3 clipmap_size;"
            "uniform float clipmap_diameter = 256;"
            "vec3 clipmap(int idx, vec3 camera, vec3 vtx, inout vec3 uv, inout vec3 clr) {"
            "   int sfc = int(ceil(vtx.y));"
            "   vec3 box = vec3(clipmap_diameter) / 2.0;"
            "   vec3 offset = clamp(camera, -box, box);"
            "   offset = trunc(offset / MESH_STRIDE) * MESH_STRIDE;"
            "   vtx.xz += offset.xz;"
            "   uv = vec3((vtx.xz / clipmap_diameter) + 0.5, 0);"
            "   clr = (sfc == 0 ? vec3(1, 0, 1) : vec3(0, 0, 1));"
            "   return vtx;"
            "}";
}

const String vs_clipmap_vertex::_get_code(Array input_vars, Array output_vars, int mode, VisualShaderNodeCustom::PortType type) {
    Dictionary io = Dictionary();

    // using size() from array may not be the integer we need
    for (int i = 0; i <= input_vars.size(); i++) {
        String input = _get_input_port_name(i) + "_in";
        io[input] = input_vars[i];
    }
    for (int i = 0; i <= output_vars.size(); i++) {
        String output = _get_output_port_name(i) + "_out";
        io[output] = output_vars[i];
    }

    String code = "// clipmap"
                "vec3 color = COLOR.rgb;"
                "{uv} = vec3(UV, 0);"
                "{vertex} = VERTEX;"
                "{vertex} = (WORLD_MATRIX * vec4({vertex}, 1)).xyz;"
                "{vertex} = clipmap(INSTANCE_ID, CAMERA_MATRIX[3].xyz, {vertex}, {uv}, color);"
                "{vertex}.y = 0.0;"
                "{diameter} = clipmap_diameter;"
                "{size} = clipmap_size;"
                "{uv2} = {uv};"
                "{uv} = {vertex};"
                "{uv} = vec3({uv}.xz + 0.5 * clipmap_diameter, 0);";

    return code.format(io);
}

