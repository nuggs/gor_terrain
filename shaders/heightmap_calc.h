/*
 * Generic Off-Road Terrain System
 * copyright (c) 2021 Anthony Goins
 * the.green.machine@gmail.com
 *
 * Based on Cartographer by Adrien de Pierres <adrien@awkwardpolygons.com>
 */

#ifndef CLIPMAP_HEIGHTMAP_CALC_H
#define CLIPMAP_HEIGHTMAP_CALC_H

#include <scene/resources/shader.h>
#include <scene/resources/visual_shader.h>

class vs_heightmap_calc : public VisualShaderNodeCustom {
    GDCLASS(vs_heightmap_calc, VisualShaderNodeCustom)

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

