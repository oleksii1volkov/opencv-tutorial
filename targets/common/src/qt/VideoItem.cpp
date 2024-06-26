#include "qt/VideoItem.hpp"
#include "opencv/video_stream.hpp"

#include <QImage>
#include <QPainter>
#include <QTimer>

VideoItem::VideoItem(QQuickItem *parent) : QQuickPaintedItem(parent) {}

std::unique_ptr<VideoStream> VideoItem::createVideoStream() { return nullptr; }

void VideoItem::play() {
    if (!videoStream_) {
        if (videoStream_ = createVideoStream(); !videoStream_) {
            return;
        }
    }

    videoStream_->open();
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [&]() {
        if (videoStream_->read(frame_)) {
            cv::cvtColor(frame_, frame_, cv::COLOR_BGR2RGB);
            image_ = QImage(frame_.data, frame_.cols, frame_.rows, frame_.step,
                            QImage::Format_RGB888);
            update();
        }
    });

    timer->start(33);
}

void VideoItem::paint(QPainter *painter) {
    if (painter != nullptr && !image_.isNull()) {
        QRectF targetRect = boundingRect();

        const float imageAspectRatio =
            float(image_.width()) / float(image_.height());
        const float rectAspectRatio =
            float(targetRect.width()) / float(targetRect.height());

        if (imageAspectRatio > rectAspectRatio) {
            float newHeight = targetRect.width() / imageAspectRatio;
            float offset = (targetRect.height() - newHeight) / 2.0;
            targetRect.setTop(targetRect.top() + offset);
            targetRect.setHeight(newHeight);
        } else {
            float newWidth = targetRect.height() * imageAspectRatio;
            float offset = (targetRect.width() - newWidth) / 2.0;
            targetRect.setLeft(targetRect.left() + offset);
            targetRect.setWidth(newWidth);
        }

        painter->drawImage(targetRect, image_);
    }
}
