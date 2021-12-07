
#include "texture_array_builder.h"

const String texture_array_builder::get_importer_name(void) {
    return "texture_array_builder";
}

const String texture_array_builder::get_visible_name(void) {
    return "TextureArrayBuilder";
}

const Array texture_array_builder::get_recognized_extensions(void) {
    Array arr;
    arr.insert(0, "tabld");
    return arr;
}

const String texture_array_builder::get_save_extension(void) {
    return "texarr";
}

const String texture_array_builder::get_resource_type(void) {
    return "TextureArray";
}

/*
 * Since we're using C++ there's not really a way to get
 * the number of items defined in an enum but since we
 * know the count, we can just do this.
 *
 * If we wanted it to be cleaner, we could define a MAX
 * or SIZE or something with the number of variables but meh.
 */
const int texture_array_builder::get_preset_count(void) {
    return MAX;
}

const String texture_array_builder::get_preset_name(int preset) {
    return "";
}

const Array texture_array_builder::get_import_options(int preset) {
    Array options = Array();

    switch(preset) {
        case DEFAULTS:
            {
                Dictionary entry;

                entry["name"] = "format";
                entry["default_value"] = FORMAT_RGBA8;
                entry["property_hint"] = PROPERTY_HINT_ENUM;
                entry["hint_string"] = "FORMAT_L8,FORMAT_LA8,FORMAT_R8,FORMAT_RG8,FORMAT_RGB8,FORMAT_RGBA8";
                options.insert(0, entry);
                entry.clear();

                entry["name"] = "compress";
                entry["default_value"] = VRAM;
                entry["property_hint"] = PROPERTY_HINT_ENUM;
                entry["hint_string"] = "Lossless,VRAM,Uncompressed";
                options.insert(1, entry);
                entry.clear();

                entry["name"] = "flags";
                entry["default_value"] = 7;
                entry["property_hint"] = PROPERTY_HINT_ENUM;
                entry["hint_string"] = "Mipmaps,Repeat,Filter";
                options.insert(2, entry);
                entry.clear();
            }
        break;
        default:
            ERR_PRINT("get_import_options: failed to read options");
        break;
    }

    return options;
}

bool texture_array_builder::get_option_visibility(String option, Dictionary options) {
    return true;
}

Error texture_array_builder::import(String source_file, String save_path, Dictionary options, Array r_platform_variants, Array r_gen_files) {
    Error err;
    FileAccess *file = FileAccess::open(source_file, FileAccess::READ, &err);

    if (err != OK) {
        file->close();
        return err;
    }
    String json = file->get_as_utf8_string();

    Variant res;
    String json_err_msg;
    int json_err_line;
    Error parsed_json = JSON::parse(json, res, json_err_msg, json_err_line);
    if (parsed_json != OK) {
        ERR_PRINT(String("Error when parsing {0}: line {1}: {2}").format(varray(source_file, json_err_line, json_err_msg)));
        return parsed_json;
    }

    Ref<multi_texture> obj = res;
    obj->set_data(res);

    // We may need to create some data but for now we're just using set_data above, just a note
    //obj->create_data(obj->get_width(), obj->get_height(), obj->get_depth(), options["format"], options["flags"]);

    Array images = Array();
    images = _parse(obj->get_data());

    if (options["compress"]) {
        err = _save_tex_vram(images, save_path, options["flags"], r_platform_variants);
    } else {
        err = _save_tex(images, String("%s.%s").format(save_path, get_save_extension()), options["compress"], -1, options["flags"]);
    }

    return err;
}

Array texture_array_builder::_parse(Variant _data) {
    Dictionary data = _data.get_data();
    Vector2 size = Vector2(data["size"][0], data["size"][1]);
    Image::Format format = data.format;
    Array images = Array();

    // lol just realized this isn't going to work...
    for (int i = 0; i <= data.layers; i++) {
        Ref<Image> image = nullptr;
        if (isalpha(i)) {
            image = _load_image(i, size);
        } else {
            image = _get_image_from_channels(i, size, format);
        }
        images.push_back(image);
    }
    return images;
}

