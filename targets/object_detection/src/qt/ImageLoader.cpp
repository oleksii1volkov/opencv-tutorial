#include "qt/ImageLoader.hpp"

#include "image_info.hpp"
#include "image_providers/contour_detector.hpp"
#include "image_providers/corner_detector.hpp"
#include "image_providers/edge_detector.hpp"
#include "image_providers/face_detector.hpp"
#include "image_providers/feature_matcher.hpp"
#include "image_providers/grid_detector.hpp"
#include "image_providers/license_plate_detector.hpp"
#include "image_providers/template_matcher.hpp"
#include "image_providers/watershed_image_provider.hpp"

#include <memory>
#include <ranges>

ImageLoader::ImageLoader() {}

void ImageLoader::load() {
    onImageInfosAdded(std::make_unique<LicensePlateDetector>()->get_images());
    onImageInfosAdded(std::make_unique<FaceDetector>()->get_images());
    onImageInfosAdded(std::make_unique<WatershedImageProvider>()->get_images());
    onImageInfosAdded(std::make_unique<FeatureMatcher>()->get_images());
    onImageInfosAdded(std::make_unique<ContourDetector>()->get_images());
    onImageInfosAdded(std::make_unique<CornerDetector>()->get_images());
    onImageInfosAdded(std::make_unique<EdgeDetector>()->get_images());
    onImageInfosAdded(std::make_unique<GridDetector>()->get_images());
    onImageInfosAdded(std::make_unique<TemplateMatcher>()->get_images());
}

void ImageLoader::addImageInfosAddedCallback(ImageInfosAddedCallback callback) {
    imageInfosAddedCallbacks_.push_back(std::move(callback));
}

void ImageLoader::onImageInfosAdded(std::vector<ImageInfo> imageInfos) {
    if (imageInfosAddedCallbacks_.empty()) {
        return;
    }

    for (auto &callback :
         imageInfosAddedCallbacks_ |
             std::views::take(imageInfosAddedCallbacks_.size() - 1)) {
        callback(imageInfos);
    }

    imageInfosAddedCallbacks_.back().operator()(std::move(imageInfos));
}
