/*
 * Generic Off-Road Terrain System
 * copyright (c) 2021 Anthony Goins
 * the.green.machine@gmail.com
 *
 * Based on Cartographer by Adrien de Pierres <adrien@awkwardpolygons.com>
 */

#ifndef SET_UV3D_H
#define SET_UV3D_H

#include <scene/resources/shader.h>
#include <scene/resources/visual_shader.h>

class vs_set_uv3d : public VisualShaderNodeCustom {
    GDCLASS(vs_set_uv3d, VisualShaderNodeCustom);

    protected:
        void _init(void);
        const String _get_name(void);
        static String _get_category(void);
        const String _get_description(void);
        const int _get_input_port_count(void);
        const String _get_input_port_name(int port);
        const PortType _get_input_port_type(int port);
        const int _get_output_port_count(void);
        const String _get_output_port_name(int port);
        const PortType _get_output_port_type(int port);
        const String _get_global_code(PortType mode);
        const String _get_code(Array input_vars, Array output_vars, int mode, PortType type);
};

#endif

