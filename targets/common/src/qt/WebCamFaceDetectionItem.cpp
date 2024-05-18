#include "qt/WebCamFaceDetectionItem.hpp"

#include "opencv/webcam_face_detection_stream.hpp"

WebCamFaceDetectionItem::WebCamFaceDetectionItem(QQuickItem *parent)
    : VideoItem(parent) {}

std::unique_ptr<VideoStream> WebCamFaceDetectionItem::createVideoStream() {
    return std::make_unique<WebCamFaceDetectionStream>();
}
