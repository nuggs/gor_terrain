/*
 * Generic Off-Road Terrain System
 * copyright (c) 2021 Anthony Goins
 * the.green.machine@gmail.com
 *
 * Based on Cartographer by Adrien de Pierres <adrien@awkwardpolygons.com>
 */

#include "heightmap_calc.h"

const String vs_heightmap_calc::_get_name(void) {
    return "heightmap_calc";
}

String vs_heightmap_calc::_get_category(void) {
    return "gor_terrain";
}

const String vs_heightmap_calc::_get_description(void) {
    return "Clipmap heightmap(?) transform node";
}

const int vs_heightmap_calc::_get_input_port_count(void) {
    return 2;
}

const String vs_heightmap_calc::_get_input_port_name(int port) {
    switch (port) {
        case 0: return "heightmap";
        case 1: return "uv";
    }
    return "heightmap";
}

const VisualShaderNodeCustom::PortType vs_heightmap_calc::_get_input_port_type(int port) {
    switch (port) {
        case 0: return PORT_TYPE_SAMPLER;
        case 1: return PORT_TYPE_VECTOR;
    }
    return PORT_TYPE_MAX;
}

const int vs_heightmap_calc::_get_output_port_count(void) {
    return 2;
}

const String vs_heightmap_calc::_get_output_port_name(int port) {
    switch (port) {
        case 0: return "normal";
        case 1: return "offset";
    }
    return "normal";
}

const VisualShaderNodeCustom::PortType vs_heightmap_calc::_get_output_port_type(int port) {
    switch (port) {
        case 0: return PORT_TYPE_VECTOR;
        case 1: return PORT_TYPE_VECTOR;
    }
    return PORT_TYPE_MAX;
}

const String vs_heightmap_calc::_get_global_code(VisualShaderNodeCustom::PortType mode) {
    return "//heightmap_calc globals"
        "uniform sampler2D heightmap : hint_black;"
        "float get_height(sampler2D hmap, vec2 uv) {"
        "    vec4 h = texture(hmap, uv);"
        "    h = uv.x > 1.0 || uv.y > 1.0 ? vec4(0) : h;"
        "    h = uv.x < 0.0 || uv.y < 0.0 ? vec4(0) : h;"
        "    return h.r;"
        "}"
        "vec3 calc_normal(sampler2D hmap, vec2 uv, float _off) {"
        "    vec3 off = vec2(_off, 0.0).xyz;"
        "    float x = get_height(hmap, uv - off.xz) - get_height(hmap, uv+off.xz);"
        "    float y = get_height(hmap, uv - off.zy) - get_height(hmap, uv+off.zy);"
        "    return normalize(vec3(x, off.x * 8.0, y));"
        "}";
}

const String vs_heightmap_calc::_get_code(Array input_vars, Array output_vars, int mode, VisualShaderNodeCustom::PortType type) {
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

    String code = "// heightmap_calc"
                "{offset} = vec3(0, get_height({heightmap_in}, {uv_in}.xy, 0);"
                "{normal} = calc_normal({heightmap_in}, {uv_in}.xy, 1.0/2048.0);";

    return code.format(io);
}

