#pragma once

#include <QQuickImageProvider>

class ImageModel;

class ImageProvider : public QQuickImageProvider {
public:
    explicit ImageProvider(ImageModel *imageModel);

    QPixmap requestPixmap(const QString &id, QSize *size,
                          const QSize &requestedSize) override;

private:
    ImageModel *imageModel_{};
};
