/*
 * Generic Off-Road Terrain System
 * copyright (c) 2021 Anthony Goins
 * the.green.machine@gmail.com
 *
 * Based on Cartographer by Adrien de Pierres <adrien@awkwardpolygons.com>
 */

#include "clipmap_transform.h"

void vs_clipmap_transform::_init(void) {
    Array defaults = Array();

    // Is there a better way to do this?
    defaults.insert(0,0);
    defaults.insert(1, Vector3(0, 0, 0));
    defaults.insert(2, 1);
    defaults.insert(3, Vector3(0, 1, 0));
    defaults.insert(4, 2);
    defaults.insert(5, Vector3(0, 0, 0));
    defaults.insert(6, Vector3(0, 0, 0));

    set_default_input_values(defaults);
}

const String vs_clipmap_transform::_get_name(void) {
    return "clipmap_transform";
}

String vs_clipmap_transform::_get_category(void) {
    return "gor_terrain";
}

const String vs_clipmap_transform::_get_description(void) {
    return "Clipmap vertex transform node";
}

const int vs_clipmap_transform::_get_input_port_count(void) {
    return 4;
}

const String vs_clipmap_transform::_get_input_port_name(int port) {
    switch (port) {
        case 0: return "vertex";
        case 1: return "normal";
        case 2: return "tangent";
        case 3: return "binormal";
    }
    return "vertex";
}

const VisualShaderNodeCustom::PortType vs_clipmap_transform::_get_input_port_type(int port) {
    switch (port) {
        case 0: return PORT_TYPE_VECTOR;
        case 1: return PORT_TYPE_VECTOR;
        case 2: return PORT_TYPE_VECTOR;
        case 3: return PORT_TYPE_VECTOR;
    }
    return PORT_TYPE_VECTOR;
}

const int vs_clipmap_transform::_get_output_port_count(void) {
    return 4;
}

const String vs_clipmap_transform::_get_output_port_name(int port) {
    switch (port) {
        case 0: return "vertex";
        case 1: return "normal";
        case 2: return "tangent";
        case 3: return "binormal";
    }
    return "vertex";
}

const VisualShaderNodeCustom::PortType vs_clipmap_transform::_get_output_port_type(int port) {
    switch (port) {
        case 0: return PORT_TYPE_VECTOR;
        case 1: return PORT_TYPE_VECTOR;
        case 2: return PORT_TYPE_VECTOR;
        case 3: return PORT_TYPE_VECTOR;
    }
    return PORT_TYPE_VECTOR;
}

const String vs_clipmap_transform::_get_global_code(VisualShaderNodeCustom::PortType mode) {
    return "";
}

const String vs_clipmap_transform::_get_code(Array input_vars, Array output_vars, int mode, VisualShaderNodeCustom::PortType type) {
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

    String code = "// clipmap_transform"
                "{vertex} = (INV_CAMERA_MATRIX * vec4({vertex_in}, 1.0)).xyz;"
                "{normal} = (INV_CAMERA_MATRIX * vec4({normal_in}, 0.0)).xyz;"
                "{binormal} = (INV_CAMERA_MATRIX * vec4({binormal_in}, 0.0)).xyz;"
                "{tangent} = (INV_CAMERA_MATRIX * vec4({tangent_in}, 0.0)).xyz;";

    return code.format(io);
}

