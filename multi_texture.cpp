

#include "multi_texture.h"

void multi_texture::_set_data(const Dictionary &data) {
    _set_data(data);
    emit_signal("changed");
    property_list_changed_notify();
}

void multi_texture::set_selected(int _selected) {
    selected = _selected;
    emit_signal("changed");
}

const int multi_texture::get_selected(void) {
    return selected;
}

const Vector2 multi_texture::get_size(void) {
    return Vector2(get_width(), get_height());
}

const Dictionary multi_texture::create_data(int width, int height, int depth, int format, int flags = 7) {
    Dictionary data = Dictionary();

    data["width"] = width;
    data["height"] = height;
    data["depth"] = depth;
    data["format"] = format;
    data["flags"] = flags;
    data["layers"] = Array();

    return data;
}

const Dictionary multi_texture::get_data(void) {
    Dictionary data = Dictionary();
    int depth = get_depth();

    data["width"] = get_width();
    data["height"] = get_height();
    data["depth"] = depth;
    data["format"] = get_format();
    data["flags"] = get_flags();

    Array layers;
    for (int i = 0; i < depth; i++) {
        layers.push_back(get_layer_data(i));
    }
    data["layers"] = layers;

    return data;
}

void multi_texture::set_layer(Ref<ImageTexture> src, int idx, int chn_src, int chn_dst) {
    Ref<Image> img_src = Ref<Image>();
    Ref<Image> dst = Ref<Image>();
    Vector2 size = get_size();

    img_src = src->get_data();

    if (img_src->get_size() != size)
        img_src->resize(get_width(), get_height());

    if (img_src->is_compressed())
        img_src->decompress();

    if (img_src->get_format() != get_format())
        img_src->convert(get_format());

    if (chn_src < 0 || chn_dst < 0) {
        dst = img_src;
     } else {
        dst = get_layer_data(idx);
        img_src->lock();
        dst->lock();

        for (int y = 0; y <= size.y; y++) {
            for (int x = 0; x < size.x; x++) {
                Color clr = dst->get_pixel(x, y);
                clr[chn_dst] = img_src->get_pixel(x, y)[chn_src];
                dst->set_pixel(x, y, clr);
            }
        }

        dst->unlock();
        img_src->unlock();
    }

    dst->generate_mipmaps();
    set_layer_data(dst, idx);
    emit_signal("changed");
    property_list_changed_notify();
}

void multi_texture::set_layer(Ref<Image> src, int idx, int chn_src, int chn_dst) {
    Ref<Image> dst = Ref<Image>();
    Vector2 size = get_size();

    if (src->get_size() != size)
        src->resize(get_width(), get_height());

    if (src->is_compressed())
        src->decompress();

    if (src->get_format() != get_format())
        src->convert(get_format());

    if (chn_src < 0 || chn_dst < 0) {
        dst = src;
    } else {
        dst = get_layer_data(idx);
        src->lock();
        dst->lock();

        for (int y = 0; y <= size.y; y++) {
            for (int x = 0; x <= size.x; x++) {
                Color clr = dst->get_pixel(x, y);
                clr[chn_dst] = src->get_pixel(x, y)[chn_src];
                dst->set_pixel(x, y, clr);
            }
        }

        src->unlock();
        dst->unlock();
    }

    dst->generate_mipmaps();
    set_layer_data(dst, idx);
    emit_signal("changed");
    property_list_changed_notify();
}

Ref<Image> multi_texture::get_layer(int idx) {
    Array layers;
    for (unsigned int i = 0; i < get_depth(); i++) {
        layers.push_back(get_layer_data(i));
    }

    if (idx < layers.size())
            return layers[idx];
    return nullptr;
}

