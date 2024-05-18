#include "opencv/webcam_object_tracking_stream.hpp"

#include <cstdint>
#include <iostream>
#include <ranges>
#include <vector>

WebCamObjectTrackingStream::WebCamObjectTrackingStream() {}

bool WebCamObjectTrackingStream::open() {
    if (!video_capture_.open(0)) {
        return false;
    }

    video_capture_.read(previous_frame_gray_);
    if (previous_frame_gray_.empty()) {
        return false;
    }

    cv::cvtColor(previous_frame_gray_, previous_frame_gray_,
                 cv::COLOR_BGR2GRAY);

    cv::goodFeaturesToTrack(previous_frame_gray_, previous_points_, 10, 0.3, 7,
                            cv::noArray(), 7);

    return true;
}

void WebCamObjectTrackingStream::close() { video_capture_.release(); }

bool WebCamObjectTrackingStream::read(cv::Mat &frame) {
    if (!video_capture_.read(frame) || frame.empty()) {
        return false;
    }

    cv::Mat frame_gray;
    cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);

    std::vector<cv::Point2f> next_points;
    std::vector<uint8_t> statuses;
    std::vector<float> errors;

    cv::calcOpticalFlowPyrLK(
        previous_frame_gray_, frame_gray, previous_points_, next_points,
        statuses, errors, cv::Size{200, 200}, 2,
        cv::TermCriteria{cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 10,
                         0.03});

    for (size_t point_index{0}; point_index < next_points.size();
         ++point_index) {
        const auto &next_point = next_points[point_index];
        const auto &previous_point = previous_points_[point_index];

        if (statuses[point_index] != 1) {
            continue;
        }

        cv::line(frame, previous_point, next_point, cv::Scalar(0, 255, 0), 1);
        cv::circle(frame, next_point, 5, cv::Scalar(0, 0, 255), -1);
    }

    previous_frame_gray_ = std::move(frame_gray);
    previous_points_ = std::move(next_points);

    return true;
}

bool WebCamObjectTrackingStream::is_opened() const {
    return video_capture_.isOpened();
}

WebCamObjectTrackingStream::~WebCamObjectTrackingStream() {
    if (is_opened()) {
        close();
    }
}
