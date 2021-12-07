
#ifndef MULTI_TEXTURE_SAVER_H
#define MULTI_TEXTURE_SAVER_H

#include <core/resource.h>
#include <core/io/resource_saver.h>

class multi_texture_saver : public ResourceFormatSaver {
    GDCLASS(multi_texture_saver, ResourceFormatSaver);

    public:
        PoolStringArray get_recognized_extensions(Ref<Resource> res);
        bool recognize(Ref<Resource> res);
        int save(String path, Ref<Resource> res, int flags);
};

#endif // MULTI_TEXTURE_SAVER_H
