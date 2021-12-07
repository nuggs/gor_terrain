
#ifndef TEXTURE_ARRAY_BUILDER_H
#define TEXTURE_ARRAY_BUILDER_H

#include <core/image.h>
#include <core/io/json.h>
#include <editor/editor_plugin.h>

#include "multi_texture.h"

class texture_array_builder : public EditorImportPlugin {
    GDCLASS(texture_array_builder, EditorImportPlugin);

    public:
        enum Presets { DEFAULTS, MAX = DEFAULTS };
        enum Compress { LOSSLESS, VRAM, UNCOMPRESSED };
        enum Format { FORMAT_L8, FORMAT_LA8, FORMAT_RG8, FORMAT_RGB8, FORMAT_RGBA8 };
        //Dictionary formats;

        const String get_importer_name(void);
        const String get_visible_name(void);
        const Array get_recognized_extensions(void);
        const String get_save_extension(void);
        const String get_resource_type(void);
        const int get_preset_count(void);
        const String get_preset_name(int preset);
        const Array get_import_options(int preset);
        bool get_option_visibility(String option, Dictionary options);
        Error import(String source_file, String save_path, Dictionary options, Array r_platform_variants, Array r_gen_files);

    protected:
        Array _parse(Variant data);
        Ref<Image> _get_image_from_channels(Dictionary channels, Vector2 size, int format);
        Ref<Image> _load_image(String path, Vector2 size, int format);
        void _save_tex_vram(Array images, String path, int flags, Array r_comp);
        Error _save_tex(Array images, String path, int compression, int vram_compression, int flags);
};

#endif // TEXTURE_ARRAY_BUILDER_H

