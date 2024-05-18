#pragma once

#include <filesystem>
#include <opencv2/opencv.hpp>

namespace utils {
void detect_faces(cv::Mat &image, cv::CascadeClassifier &classifier);

std::filesystem::path get_data_folder();

cv::CascadeClassifier get_frontalface_classifier();
cv::CascadeClassifier get_license_plate_classifier();
} // namespace utils
