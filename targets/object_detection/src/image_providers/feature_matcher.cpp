#include "image_providers/feature_matcher.hpp"
#include "utils.hpp"

#include <opencv2/opencv.hpp>

#include <filesystem>

namespace {
std::vector<ImageInfo> getMatchesUsingORBAndBF(const auto &reeses_image,
                                               const auto &cereals_image) {
    const auto orb = cv::ORB::create();

    std::vector<cv::KeyPoint> cereals_keypoints;
    cv::Mat cereals_descriptors;
    orb->detectAndCompute(cereals_image, cv::noArray(), cereals_keypoints,
                          cereals_descriptors);

    std::vector<cv::KeyPoint> reeses_keypoints;
    cv::Mat reeses_descriptors;
    orb->detectAndCompute(reeses_image, cv::noArray(), reeses_keypoints,
                          reeses_descriptors);

    const auto matcher = cv::BFMatcher::create(cv::NORM_HAMMING, true);
    std::vector<cv::DMatch> matches;

    matcher->match(reeses_descriptors, cereals_descriptors, matches);
    cv::Mat matches_image;
    cv::drawMatches(reeses_image, reeses_keypoints, cereals_image,
                    cereals_keypoints, matches, matches_image);

    return {{.title = "Reeses and cereals features using ORB and BF matcher",
             .image = std::move(matches_image)}};
}

std::vector<ImageInfo> getMatchesUsingSIFTAndBF(const auto &reeses_image,
                                                const auto &cereals_image) {
    const auto sift = cv::SIFT::create();

    std::vector<cv::KeyPoint> cereals_keypoints;
    cv::Mat cereals_descriptors;
    sift->detectAndCompute(cereals_image, cv::noArray(), cereals_keypoints,
                           cereals_descriptors);

    std::vector<cv::KeyPoint> reeses_keypoints;
    cv::Mat reeses_descriptors;
    sift->detectAndCompute(reeses_image, cv::noArray(), reeses_keypoints,
                           reeses_descriptors);

    const auto matcher = cv::BFMatcher::create();
    std::vector<std::vector<cv::DMatch>> matches;
    matcher->knnMatch(reeses_descriptors, cereals_descriptors, matches, 2);

    std::vector<cv::DMatch> good_matches;
    good_matches.reserve(matches.size());

    for (const auto &match : matches) {
        if (match[0].distance < 0.75 * match[1].distance) {
            good_matches.push_back(match[0]);
        }
    }

    cv::Mat matches_image;
    cv::drawMatches(reeses_image, reeses_keypoints, cereals_image,
                    cereals_keypoints, good_matches, matches_image);

    return {{.title = "Reeses and cereals features using SIFT and BF matcher",
             .image = std::move(matches_image)}};
}

std::vector<ImageInfo> getMatchesUsingSIFTAndFLANN(const auto &reeses_image,
                                                   const auto &cereals_image) {
    const auto sift = cv::SIFT::create();

    std::vector<cv::KeyPoint> cereals_keypoints;
    cv::Mat cereals_descriptors;
    sift->detectAndCompute(cereals_image, cv::noArray(), cereals_keypoints,
                           cereals_descriptors);

    std::vector<cv::KeyPoint> reeses_keypoints;
    cv::Mat reeses_descriptors;
    sift->detectAndCompute(reeses_image, cv::noArray(), reeses_keypoints,
                           reeses_descriptors);

    const auto matcher = cv::FlannBasedMatcher::create();
    std::vector<std::vector<cv::DMatch>> matches;
    matcher->knnMatch(reeses_descriptors, cereals_descriptors, matches, 2);

    std::vector<cv::DMatch> good_matches;
    good_matches.reserve(matches.size());

    for (const auto &match : matches) {
        if (match[0].distance < 0.75 * match[1].distance) {
            good_matches.push_back(match[0]);
        }
    }

    cv::Mat matches_image;
    cv::drawMatches(reeses_image, reeses_keypoints, cereals_image,
                    cereals_keypoints, good_matches, matches_image);

    return {
        {.title = "Reeses and cereals features using SIFT and FLANN matcher",
         .image = std::move(matches_image)}};
}
} // namespace

std::vector<ImageInfo> FeatureMatcher::get_images() {
    const auto data_folder_path = utils::get_data_folder();

    const auto cereals_image_path = data_folder_path / "many_cereals.jpg";
    const auto cereals_image =
        cv::imread(cereals_image_path.string(), cv::IMREAD_COLOR);

    const auto reeses_image_path = data_folder_path / "reeses_puffs.png";
    const auto reeses_image =
        cv::imread(reeses_image_path.string(), cv::IMREAD_COLOR);

    std::vector<ImageInfo> imageInfos;
    imageInfos.append_range(
        getMatchesUsingORBAndBF(reeses_image, cereals_image));
    imageInfos.append_range(
        getMatchesUsingSIFTAndBF(reeses_image, cereals_image));
    imageInfos.append_range(
        getMatchesUsingSIFTAndFLANN(reeses_image, cereals_image));

    return imageInfos;
}
