#pragma once

#include "opencv/video_stream.hpp"

#include <QImage>
#include <QQuickPaintedItem>

#include <memory>
#include <opencv2/opencv.hpp>

class VideoItem : public QQuickPaintedItem {
    Q_OBJECT
    QML_ELEMENT
public:
    VideoItem(QQuickItem *parent = nullptr);
    virtual ~VideoItem() = default;

    void paint(QPainter *painter) override;
    Q_INVOKABLE void play();

private:
    virtual std::unique_ptr<VideoStream> createVideoStream();

private:
    std::unique_ptr<VideoStream> videoStream_;
    QImage image_;
    cv::Mat frame_;
};
