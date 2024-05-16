#pragma once

#include "image_provider.hpp"

class ContourDetector : public ImageProvider {
public:
    std::vector<ImageInfo> get_images() override;
};
