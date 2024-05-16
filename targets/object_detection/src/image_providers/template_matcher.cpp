#include "image_providers/template_matcher.hpp"
#include "utils.hpp"

#include <opencv2/opencv.hpp>

#include <filesystem>
#include <format>
#include <vector>

std::vector<ImageInfo> TemplateMatcher::get_images() {
    const auto data_folder_path = utils::get_data_folder();
    const auto sammy_image_path = data_folder_path / "sammy.jpg";
    const auto sammy_face_image_path = data_folder_path / "sammy_face.jpg";

    const auto sammy_image =
        cv::imread(sammy_image_path.string(), cv::IMREAD_COLOR);
    const auto sammy_face_image =
        cv::imread(sammy_face_image_path.string(), cv::IMREAD_COLOR);

    std::vector<cv::TemplateMatchModes> match_modes{
        cv::TM_SQDIFF,       cv::TM_SQDIFF_NORMED, cv::TM_CCORR,
        cv::TM_CCORR_NORMED, cv::TM_CCOEFF,        cv::TM_CCOEFF_NORMED};

    std::vector<ImageInfo> image_infos;
    image_infos.reserve(match_modes.size());

    for (auto mode : match_modes) {
        auto sammy_image_copy = sammy_image.clone();

        cv::Mat match_result;
        cv::matchTemplate(sammy_image, sammy_face_image, match_result, mode);

        cv::Point match_min_location{};
        cv::Point match_max_location{};

        cv::minMaxLoc(match_result, nullptr, nullptr, &match_min_location,
                      &match_max_location);

        if (mode == cv::TM_SQDIFF || mode == cv::TM_SQDIFF_NORMED) {
            std::swap(match_min_location, match_max_location);
        }

        cv::Rect2d match_rect{
            match_max_location,
            cv::Point(match_max_location.x + sammy_face_image.cols,
                      match_max_location.y + sammy_face_image.rows)};

        cv::rectangle(sammy_image_copy, match_rect, cv::Scalar(0, 0, 255), 2);

        image_infos.push_back(
            {.title = std::format("Template matching mode: {}",
                                  static_cast<int>(mode)),
             .image = std::move(sammy_image_copy)});
    }

    return image_infos;
}
