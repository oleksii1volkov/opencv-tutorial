#include "opencv/webcam_face_detection_stream.hpp"
#include "utils.hpp"

WebCamFaceDetectionStream::WebCamFaceDetectionStream()
    : face_classifier_{utils::get_frontalface_classifier()} {}

bool WebCamFaceDetectionStream::open() { return video_capture_.open(0); }

void WebCamFaceDetectionStream::close() { video_capture_.release(); }

bool WebCamFaceDetectionStream::read(cv::Mat &frame) {
    if (!video_capture_.read(frame)) {
        return false;
    }

    utils::detect_faces(frame, face_classifier_);

    return true;
}

bool WebCamFaceDetectionStream::is_opened() const {
    return video_capture_.isOpened();
}

WebCamFaceDetectionStream::~WebCamFaceDetectionStream() {
    if (is_opened()) {
        close();
    }
}
