#pragma once

#include "image_provider.hpp"

class LicensePlateDetector : public ImageProvider {
public:
    std::vector<ImageInfo> get_images() override;
};
