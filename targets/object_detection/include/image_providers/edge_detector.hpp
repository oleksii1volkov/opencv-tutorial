#pragma once

#include "image_provider.hpp"

class EdgeDetector : public ImageProvider {
public:
    std::vector<ImageInfo> get_images() override;
};
