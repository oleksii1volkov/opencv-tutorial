#include "image_providers/contour_detector.hpp"
#include "utils.hpp"

#include <opencv2/opencv.hpp>

#include <cstdlib>
#include <filesystem>
#include <vector>

namespace {
auto find_and_draw_contours(const auto &image_path) {
    cv::Mat image = cv::imread(image_path.string(), cv::IMREAD_GRAYSCALE);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(image, contours, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
    cv::Mat contours_image{image.size(), image.type(), cv::Scalar{0, 0, 0}};

    for (const auto &contour : contours) {
        cv::drawContours(contours_image, contours, -1,
                         cv::Scalar{255, 255, 255}, 1);
    }

    return contours_image;
}
} // namespace

std::vector<ImageInfo> ContourDetector::get_images() {
    const auto data_folder_path = utils::get_data_folder();

    const auto contours_image_path = data_folder_path / "internal_external.png";
    const auto sammy_image_path = data_folder_path / "sammy.jpg";

    return {{.title = "Simple contours",
             .image = find_and_draw_contours(contours_image_path)},
            {.title = "Sammy's contours",
             .image = find_and_draw_contours(sammy_image_path)}};
}
