#pragma once

#include "image_info.hpp"

#include <QAbstractListModel>
#include <QHash>
#include <QPixmap>
#include <QString>

#include <thread>

class ImageProvider;

class ImageModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum ImageRoles { IdRole = Qt::UserRole + 1, TitleRole, ImageRole };

    explicit ImageModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void appendImages(std::vector<ImageInfo> imageInfos);

    QPixmap getImage(const QString &imageId) const;

private:
    std::vector<std::pair<ImageInfo, QString>> imageInfos_;
    QHash<QString, size_t> imageInfosIds_;
    mutable std::recursive_mutex imageInfosMutex_;
};
