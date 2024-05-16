#pragma once

#include "image_info.hpp"
#include <vector>

class ImageProvider {
public:
    virtual ~ImageProvider() = default;
    virtual std::vector<ImageInfo> get_images() = 0;
};
