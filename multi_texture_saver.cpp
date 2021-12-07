
#include "core/object.h"
#include "multi_texture.h"
#include "multi_texture_saver.h"

PoolStringArray multi_texture_saver::get_recognized_extensions(Ref<Resource> res) {
    if (recognize(res)) {
        PoolStringArray loltest = PoolStringArray();
        loltest.push_back("texarr");
        return loltest;
    }
    return PoolStringArray();
}

bool multi_texture_saver::recognize(Ref<Resource> res) {
    if (res->get_class_static() == "multi_texture")
        return true;
    return false;
}

int multi_texture_saver::save(String path, Ref<Resource> res, int flags) {
//    texture_array_builder imp = texture_array_builder.new();
    return 0;
}
