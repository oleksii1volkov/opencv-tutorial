#pragma once

#include "image_provider.hpp"

class FaceDetector : public ImageProvider {
public:
    std::vector<ImageInfo> get_images() override;
};
