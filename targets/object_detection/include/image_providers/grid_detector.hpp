#pragma once

#include "image_provider.hpp"

class GridDetector : public ImageProvider {
public:
    std::vector<ImageInfo> get_images() override;
};
