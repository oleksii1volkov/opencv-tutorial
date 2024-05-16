#pragma once

#include "image_info.hpp"

#include <functional>
#include <vector>

class ImageLoader {
public:
    using ImageInfosAddedCallback = std::function<void(std::vector<ImageInfo>)>;
    ImageLoader();

    void load();

    void addImageInfosAddedCallback(ImageInfosAddedCallback callback);

private:
    void onImageInfosAdded(std::vector<ImageInfo> imageInfos);

private:
    std::vector<ImageInfosAddedCallback> imageInfosAddedCallbacks_;
};
