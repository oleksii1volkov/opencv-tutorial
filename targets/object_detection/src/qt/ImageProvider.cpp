#include "qt/ImageProvider.hpp"
#include "qt/ImageModel.hpp"

ImageProvider::ImageProvider(ImageModel *imageModel)
    : QQuickImageProvider(QQuickImageProvider::Pixmap),
      imageModel_{imageModel} {}

QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size,
                                     const QSize &requestedSize) {
    QPixmap pixmap = imageModel_->getImage(id);

    if (size) {
        *size = pixmap.size();
    }

    return pixmap;
}
