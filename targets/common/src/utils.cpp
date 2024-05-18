#include "utils.hpp"
#include "config.h"

#include <filesystem>
#include <opencv2/opencv.hpp>

namespace utils {
void detect_faces(cv::Mat &image, cv::CascadeClassifier &classifier) {
    std::vector<cv::Rect> faces;

    classifier.detectMultiScale(image, faces);

    for (const auto &face : faces) {
        cv::rectangle(image, face, cv::Scalar(0, 255, 0));
    }
}

std::filesystem::path get_data_folder() {
    return std::filesystem::path{std::string{WORKSPACE_DIR}} / "data";
}

cv::CascadeClassifier get_frontalface_classifier() {
    const auto data_folder_path = get_data_folder();
    const auto frontalface_classifier_path =
        data_folder_path / "haarcascades" /
        "haarcascade_frontalface_default.xml";

    return cv::CascadeClassifier(frontalface_classifier_path.string());
}

cv::CascadeClassifier get_license_plate_classifier() {
    const auto data_folder_path = get_data_folder();
    const auto license_plate_classifier_path =
        data_folder_path / "haarcascades" /
        "haarcascade_licence_plate_rus_16stages.xml";

    return cv::CascadeClassifier(license_plate_classifier_path.string());
}
} // namespace utils
