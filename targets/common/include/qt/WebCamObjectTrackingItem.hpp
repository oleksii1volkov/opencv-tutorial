#pragma once

#include "VideoItem.hpp"

class WebCamObjectTrackingItem : public VideoItem {
    Q_OBJECT
    QML_ELEMENT
public:
    WebCamObjectTrackingItem(QQuickItem *parent = nullptr);
    ~WebCamObjectTrackingItem() override = default;

private:
    std::unique_ptr<VideoStream> createVideoStream() override;
};
