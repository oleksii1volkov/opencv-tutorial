#pragma once

#include "image_provider.hpp"

class CornerDetector : public ImageProvider {
public:
    std::vector<ImageInfo> get_images() override;
};
