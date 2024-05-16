#include "image_providers/edge_detector.hpp"
#include "utils.hpp"

#include <opencv2/opencv.hpp>

#include <cstdlib>
#include <filesystem>
#include <vector>

std::vector<ImageInfo> EdgeDetector::get_images() {
    const auto data_folder_path = utils::get_data_folder();
    const auto sammy_image_path = data_folder_path / "sammy_face.jpg";

    const auto sammy_image =
        cv::imread(sammy_image_path.string(), cv::IMREAD_COLOR);
    cv::Mat sammy_image_edges;

    cv::blur(sammy_image, sammy_image, {3, 3});
    cv::Canny(sammy_image, sammy_image_edges, 100, 200);

    return {{.title = "Sammy's edges", .image = std::move(sammy_image_edges)}};
}
