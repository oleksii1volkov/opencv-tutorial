#pragma once

#include "video_stream.hpp"

#include <opencv2/opencv.hpp>
#include <vector>

class WebCamObjectTrackingStream : public VideoStream {
public:
    WebCamObjectTrackingStream();

    bool open() override;
    void close() override;
    bool read(cv::Mat &frame) override;
    bool is_opened() const override;

    ~WebCamObjectTrackingStream() override;

private:
    cv::VideoCapture video_capture_;
    cv::Mat previous_frame_gray_;
    std::vector<cv::Point2f> previous_points_;
};
