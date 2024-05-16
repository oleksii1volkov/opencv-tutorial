#include "image_providers/license_plate_detector.hpp"
#include "utils.hpp"

#include <filesystem>
#include <vector>

std::vector<ImageInfo> LicensePlateDetector::get_images() {
    const auto data_folder_path = utils::get_data_folder();
    const auto license_plates_image_path = data_folder_path / "car_plate.jpg";
    auto license_plates_image =
        cv::imread(license_plates_image_path.string(), cv::IMREAD_COLOR);

    cv::Mat license_plates_image_grayscale;
    cv::cvtColor(license_plates_image, license_plates_image_grayscale,
                 cv::COLOR_BGR2GRAY);
    auto license_plate_classifier = utils::get_license_plate_classifier();

    std::vector<cv::Rect> license_plate_rects;
    license_plate_classifier.detectMultiScale(license_plates_image_grayscale,
                                              license_plate_rects);

    auto blurred_license_plates_image = license_plates_image.clone();

    for (const auto &license_plate_rect : license_plate_rects) {
        auto license_plate_image =
            blurred_license_plates_image(license_plate_rect);
        cv::GaussianBlur(license_plate_image, license_plate_image, {7, 7}, 0);
        blurred_license_plates_image(license_plate_rect) = license_plate_image;
        cv::rectangle(license_plates_image, license_plate_rect, {0, 255, 0}, 3);
        cv::rectangle(blurred_license_plates_image, license_plate_rect,
                      {0, 255, 0}, 3);
    }

    // cv::Mat combined_image{license_plates_image.rows,
    //                        2 * license_plates_image.cols,
    //                        license_plates_image.type()};

    // license_plates_image.copyTo(combined_image(
    //     cv::Rect{0, 0, license_plates_image.cols,
    //     license_plates_image.rows}));
    // blurred_license_plates_image.copyTo(combined_image(
    //     cv::Rect{license_plates_image.cols, 0, license_plates_image.cols,
    //              license_plates_image.rows}));

    return {
        {.title = "License plates", .image = std::move(license_plates_image)},
        {.title = "Blurred license plates",
         .image = std::move(blurred_license_plates_image)}};
}
