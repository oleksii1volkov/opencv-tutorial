#pragma once

#include "image_provider.hpp"

class TemplateMatcher : public ImageProvider {
public:
    std::vector<ImageInfo> get_images() override;
};
