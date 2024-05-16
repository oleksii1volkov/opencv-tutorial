#include "image_providers/watershed_image_provider.hpp"
#include "utils.hpp"

#include <cstdint>
#include <filesystem>
#include <print>

std::vector<ImageInfo> WatershedImageProvider::get_images() {
    const auto data_folder_path = utils::get_data_folder();
    const auto image_path = data_folder_path / "pennies.jpg";

    const auto image = cv::imread(image_path.string(), cv::IMREAD_COLOR);

    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);

    cv::Mat blured_image;
    cv::medianBlur(gray_image, blured_image, 35);

    cv::Mat thresholded_image;
    cv::threshold(blured_image, thresholded_image, 0, 255,
                  cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
    cv::morphologyEx(thresholded_image, thresholded_image, cv::MORPH_OPEN,
                     cv::Mat::ones(3, 3, CV_8UC1), cv::Point{-1, -1}, 3);

    cv::Mat foreground_image;
    cv::distanceTransform(thresholded_image, foreground_image, cv::DIST_L2, 5);

    double min_value{};
    double max_value{};
    cv::minMaxLoc(foreground_image, &min_value, &max_value);
    cv::threshold(foreground_image, foreground_image, 0.7 * max_value, 255,
                  cv::THRESH_BINARY);
    foreground_image.convertTo(foreground_image, CV_8UC1,
                               255.0 / (max_value - min_value),
                               -min_value * 255.0 / (max_value - min_value));

    cv::Mat unknown_image;
    cv::subtract(thresholded_image, foreground_image, unknown_image,
                 cv::noArray(), CV_8UC1);

    cv::Mat components;
    const auto components_count =
        cv::connectedComponents(foreground_image, components);

    cv::minMaxLoc(components, &min_value, &max_value);
    components.convertTo(components, CV_8UC1, 255.0 / (max_value - min_value),
                         -min_value * 255.0 / (max_value - min_value));

    cv::Mat mask = (components == 0);
    components.setTo(25, mask);
    mask = (unknown_image == 255);
    components.setTo(0, mask);
    components.convertTo(components, CV_32SC1);

    cv::watershed(image, components);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(components, contours, cv::RETR_CCOMP,
                     cv::CHAIN_APPROX_SIMPLE);

    cv::drawContours(image, contours, -1, cv::Scalar{0, 255, 0}, 3);

    return {{.title = "Distance transformed pennies image",
             .image = std::move(image)}};
}
