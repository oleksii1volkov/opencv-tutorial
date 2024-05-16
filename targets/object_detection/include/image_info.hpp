#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class ImageInfo {
public:
    std::string title;
    cv::Mat image;
};
