#pragma once

#include "image_provider.hpp"

class FeatureMatcher : public ImageProvider {
public:
    std::vector<ImageInfo> get_images() override;
};
