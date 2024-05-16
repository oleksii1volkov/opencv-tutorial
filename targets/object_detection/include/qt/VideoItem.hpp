#include <QQuickPaintedItem>

#include <QImage>
#include <opencv2/opencv.hpp>

class VideoItem : public QQuickPaintedItem {
    Q_OBJECT
    QML_ELEMENT
public:
    VideoItem(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;

    Q_INVOKABLE void startCapture();

private:
    cv::VideoCapture video_capture_;
    cv::Mat frame_;
    cv::CascadeClassifier face_classifier_;
    QImage image_;
};
