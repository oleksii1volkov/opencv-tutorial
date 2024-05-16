#include "image_providers/face_detector.hpp"
#include "utils.hpp"

#include <opencv2/opencv.hpp>

#include <filesystem>

std::vector<ImageInfo> FaceDetector::get_images() {
    const auto data_folder_path = utils::get_data_folder();
    const auto nadia_image_path = data_folder_path / "Nadia_Murad.jpg";
    const auto denis_image_path = data_folder_path / "Denis_Mukwege.jpg";
    const auto solvay_image_path = data_folder_path / "solvay_conference.jpg";

    auto frontalface_classifier = utils::get_frontalface_classifier();

    auto nadia_image =
        cv::imread(nadia_image_path.string(), cv::IMREAD_GRAYSCALE);
    auto denis_image =
        cv::imread(denis_image_path.string(), cv::IMREAD_GRAYSCALE);
    auto solvay_image =
        cv::imread(solvay_image_path.string(), cv::IMREAD_GRAYSCALE);

    utils::detect_faces(nadia_image, frontalface_classifier);
    utils::detect_faces(denis_image, frontalface_classifier);
    utils::detect_faces(solvay_image, frontalface_classifier);

    return {{.title = "Nadia's face", .image = std::move(nadia_image)},
            {.title = "Denis's face", .image = std::move(denis_image)},
            {.title = "Solvay faces", .image = std::move(solvay_image)}};
}
