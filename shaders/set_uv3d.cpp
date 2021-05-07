/*
 * Generic Off-Road Terrain System
 * copyright (c) 2021 Anthony Goins
 * the.green.machine@gmail.com
 *
 * Based on Cartographer by Adrien de Pierres <adrien@awkwardpolygons.com>
 */

#include "set_uv3d.h"

void vs_set_uv3d::_init(void) {
    Array defaults = Array();

    // Is there a better way to do this?
    defaults.insert(0, 1);
    defaults.insert(1, 1.0);

    set_default_input_values(defaults);
}

const String vs_set_uv3d::_get_name(void) {
    return "set_uv3d";
}

String vs_set_uv3d::_get_category(void) {
    return "gor_terrain";
}

const String vs_set_uv3d::_get_description(void) {
    return "Set UV3D varying";
}

const int vs_set_uv3d::_get_input_port_count(void) {
    return 2;
}

const String vs_set_uv3d::_get_input_port_name(int port) {
    switch (port) {
        case 0: return "position";
        case 1: return "diameter";
    }
    return "position";
}

const VisualShaderNodeCustom::PortType vs_set_uv3d::_get_input_port_type(int port) {
    switch (port) {
        case 0: return PORT_TYPE_VECTOR;
        case 1: return PORT_TYPE_SCALAR;
    }
    return PORT_TYPE_MAX;
}

const int vs_set_uv3d::_get_output_port_count(void) {
    return 1;
}

const String vs_set_uv3d::_get_output_port_name(int port) {
    switch (port) {
        case 0: return "uv3d";
    }
    return "uv3d";
}

const VisualShaderNodeCustom::PortType vs_set_uv3d::_get_output_port_type(int port) {
    switch (port) {
        case 0: return PORT_TYPE_VECTOR;
    }
    return PORT_TYPE_MAX;
}

const String vs_set_uv3d::_get_global_code(VisualShaderNodeCustom::PortType mode) {
    return "// set_uv3d globals"
            "varying vec3 UV3D;";
}

const String vs_set_uv3d::_get_code(Array input_vars, Array output_vars, int mode, VisualShaderNodeCustom::PortType type) {
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

    String code = "// set_uv3d"
                "UV3D = {position_in};"
                "UV3D += 0.5 * {diameter_in};"
                "{uv3d} = UV3D;";

    return code.format(io);
}

