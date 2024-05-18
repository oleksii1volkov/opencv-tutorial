#include "qt/WebCamObjectTrackingItem.hpp"
#include "opencv/webcam_object_tracking_stream.hpp"

WebCamObjectTrackingItem::WebCamObjectTrackingItem(QQuickItem *parent)
    : VideoItem(parent) {}

std::unique_ptr<VideoStream> WebCamObjectTrackingItem::createVideoStream() {
    return std::make_unique<WebCamObjectTrackingStream>();
}
