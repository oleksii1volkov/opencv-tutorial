#include "image_providers/corner_detector.hpp"
#include "utils.hpp"

#include <opencv2/opencv.hpp>

#include <cstdlib>
#include <filesystem>
#include <vector>

namespace {
auto read_image(const auto &image_path) {
    auto image = cv::imread(image_path.string(), cv::IMREAD_COLOR);
    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);

    return std::make_tuple(std::move(image), std::move(gray_image));
}

auto corner_harris(const auto &image_path) {
    auto [image, gray_image] = read_image(image_path);

    cv::Mat corners;
    cv::cornerHarris(gray_image, corners, 3, 3, 0.04);
    cv::dilate(corners, corners,
               cv::getStructuringElement(cv::MORPH_RECT, {3, 3}));

    double max_value{};
    cv::minMaxLoc(corners, nullptr, &max_value);
    cv::Mat mask = corners > 0.01 * max_value;

    cv::Mat colored_mask;
    cv::cvtColor(mask, colored_mask, cv::COLOR_GRAY2BGR);

    image.setTo(cv::Scalar(0, 255, 0), colored_mask);

    return image;
}

auto good_features_to_track(const auto &image_path) {
    auto [image, gray_image] = read_image(image_path);

    std::vector<cv::Point2f> corners;
    cv::goodFeaturesToTrack(gray_image, corners, 100, 0.01, 10);

    for (const auto &corner : corners) {
        cv::circle(image, corner, 3, cv::Scalar(0, 0, 255), -1);
    }

    return image;
}
} // namespace

std::vector<ImageInfo> CornerDetector::get_images() {
    const auto data_folder_path = utils::get_data_folder();
    const auto flat_chess_image_path = data_folder_path / "flat_chessboard.png";
    const auto real_chess_image_path = data_folder_path / "real_chessboard.jpg";

    const auto flat_chess_image_harris = corner_harris(flat_chess_image_path);
    const auto real_chess_image_harris = corner_harris(real_chess_image_path);

    const auto flat_chess_image_good_features =
        good_features_to_track(flat_chess_image_path);
    const auto real_chess_image_good_features =
        good_features_to_track(real_chess_image_path);

    return {{.title = "Flat chess Harris Corner Detection",
             .image = std::move(flat_chess_image_harris)},
            {.title = "Real chess Harris Corner Detection",
             .image = std::move(real_chess_image_harris)},
            {.title = "Flat chess Good features to track",
             .image = std::move(flat_chess_image_good_features)},
            {.title = "Real chess Good features to track",
             .image = std::move(real_chess_image_good_features)}};
}
