/*
 * Generic Off-Road Terrain System
 * copyright (c) 2021 Anthony Goins
 * the.green.machine@gmail.com
 *
 * Based on Cartographer by Adrien de Pierres <adrien@awkwardpolygons.com>
 */

#include "tangent_space.h"

void vs_tangent_space::_init(void) {
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

const String vs_tangent_space::_get_name(void) {
    return "tangent_space";
}

String vs_tangent_space::_get_category(void) {
    return "gor_terrain";
}

const String vs_tangent_space::_get_description(void) {
    return "Get tangent and binormal from normal input";
}

const int vs_tangent_space::_get_input_port_count(void) {
    return 1;
}

const String vs_tangent_space::_get_input_port_name(int port) {
    switch (port) {
        case 0: return "normal";
    }
    return "normal";
}

const VisualShaderNodeCustom::PortType vs_tangent_space::_get_input_port_type(int port) {
    switch (port) {
        case 0: return PORT_TYPE_VECTOR;
    }
    return PORT_TYPE_MAX;
}

const int vs_tangent_space::_get_output_port_count(void) {
    return 3;
}

const String vs_tangent_space::_get_output_port_name(int port) {
    switch (port) {
        case 0: return "normal";
        case 1: return "tangent";
        case 2: return "binormal";
    }
    return "normal";
}

const VisualShaderNodeCustom::PortType vs_tangent_space::_get_output_port_type(int port) {
    switch (port) {
        case 0: return PORT_TYPE_VECTOR;
        case 1: return PORT_TYPE_VECTOR;
        case 2: return PORT_TYPE_VECTOR;
    }
    return PORT_TYPE_MAX;
}

const String vs_tangent_space::_get_global_code(VisualShaderNodeCustom::PortType mode) {
    return "";
}

const String vs_tangent_space::_get_code(Array input_vars, Array output_vars, int mode, VisualShaderNodeCustom::PortType type) {
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

    String code = "// tangent_space"
                "{normal} = {normal_in};"
                "{tangent} = vec3(0.0,0.0,-1.0) * ({normal}.x);"
                "{tangent} += vec3(1.0,0.0,0.0) * ({normal}.y);"
                "{tangent} += vec3(1.0,0.0,0.0) * ({normal}.z);"
                "{tangent} = normalize({tangent});"
                "{binormal} = vec3(0.0,-1.0,0.0) * abs({normal}.x);"
                "{binormal} += vec3(0.0,0.0,-1.0) * abs({normal}.y);"
                "{binormal} += vec3(0.0,-1.0,0.0) * abs({normal}.z);"
                "{binormal} = normalize({binormal});";

    return code.format(io);
}

