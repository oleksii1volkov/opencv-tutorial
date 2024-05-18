#pragma once

#include "VideoItem.hpp"

class WebCamFaceDetectionItem : public VideoItem {
    Q_OBJECT
    QML_ELEMENT
public:
    WebCamFaceDetectionItem(QQuickItem *parent = nullptr);
    ~WebCamFaceDetectionItem() override = default;

private:
    std::unique_ptr<VideoStream> createVideoStream() override;
};
