#pragma once

#include "video_stream.hpp"

#include <opencv2/opencv.hpp>

class WebCamFaceDetectionStream : public VideoStream {
public:
    WebCamFaceDetectionStream();

    bool open() override;
    void close() override;
    bool read(cv::Mat &frame) override;
    bool is_opened() const override;

    ~WebCamFaceDetectionStream() override;

private:
    cv::VideoCapture video_capture_;
    cv::CascadeClassifier face_classifier_;
};
