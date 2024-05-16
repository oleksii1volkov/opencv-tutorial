#include "image_providers/grid_detector.hpp"
#include "utils.hpp"

#include <opencv2/opencv.hpp>

#include <cstdlib>
#include <filesystem>
#include <vector>

std::vector<ImageInfo> GridDetector::get_images() {
    const auto data_folder_path = utils::get_data_folder();

    const auto chessboard_image_path = data_folder_path / "flat_chessboard.png";
    const auto chessboard_image =
        cv::imread(chessboard_image_path.string(), cv::IMREAD_COLOR);
    const cv::Size chessboard_size{7, 7};
    std::vector<cv::Point2f> chessboard_corners;
    const auto chessboard_found = cv::findChessboardCorners(
        chessboard_image, chessboard_size, chessboard_corners);
    cv::drawChessboardCorners(chessboard_image, chessboard_size,
                              chessboard_corners, chessboard_found);

    const auto real_chessboard_image_path =
        data_folder_path / "real_chessboard.jpg";
    const auto real_chessboard_image =
        cv::imread(real_chessboard_image_path.string(), cv::IMREAD_COLOR);
    const cv::Size real_chessboard_size{7, 7};
    std::vector<cv::Point2f> real_chessboard_corners;
    const auto real_chessboard_found = cv::findChessboardCorners(
        real_chessboard_image, real_chessboard_size, real_chessboard_corners);
    cv::drawChessboardCorners(real_chessboard_image, real_chessboard_size,
                              real_chessboard_corners, real_chessboard_found);

    const auto circle_grid_image_path = data_folder_path / "dot_grid.png";
    const auto circle_grid_image =
        cv::imread(circle_grid_image_path.string(), cv::IMREAD_COLOR);
    const cv::Size circle_grid_size{10, 10};
    std::vector<cv::Point2f> circle_grid_corners;
    const auto circle_grid_found = cv::findCirclesGrid(
        circle_grid_image, circle_grid_size, circle_grid_corners);
    cv::drawChessboardCorners(circle_grid_image, circle_grid_size,
                              circle_grid_corners, circle_grid_found);

    return {
        {.title = "Flat chess Grid", .image = std::move(chessboard_image)},
        {.title = "Real chess grid", .image = std::move(real_chessboard_image)},
        {.title = "Circle grid", .image = std::move(circle_grid_image)}};
}
