
#ifndef MULTI_TEXTURE_H
#define MULTI_TEXTURE_H

#include <core/image.h>
#include <scene/resources/texture.h>

class multi_texture : public TextureArray {
    GDCLASS(multi_texture, TextureArray);

    public:
        void set_selected(int _selected);
        const int get_selected(void);
        const Vector2 get_size(void);
        const Dictionary create_data(int width, int height, int depth, int format, int flags);
        void set_layer(Ref<ImageTexture> src, int idx, int chn_src, int chn_dst);
        void set_layer(Ref<Image> src, int idx, int chn_src, int chn_dst);
        Ref<Image> get_layer(int idx);
        void set_data(const Dictionary &data) { _set_data(data); };
        const Dictionary get_data(void);

    protected:
        void _set_data(const Dictionary &data);

    private:
        int selected = -1;
};

#endif // MULTI_TEXTURE_H
