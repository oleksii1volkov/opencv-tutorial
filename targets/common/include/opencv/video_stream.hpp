#pragma once

#include <opencv2/opencv.hpp>

class VideoStream {
public:
    virtual bool open() = 0;
    virtual void close() = 0;
    virtual bool read(cv::Mat &frame) = 0;
    virtual bool is_opened() const = 0;

    virtual ~VideoStream() = default;
};
