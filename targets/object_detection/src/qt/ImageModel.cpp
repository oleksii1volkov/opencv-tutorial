#include "qt/ImageModel.hpp"
#include "qt/ImageProvider.hpp"

#include <QByteArray>
#include <QCryptographicHash>
#include <QHash>
#include <QImage>
#include <QPixMap>

#include <print>

namespace {
std::string matTypeToString(int type) {
    std::string r;

    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chanels = 1 + (type >> CV_CN_SHIFT);

    switch (depth) {
    case CV_8U:
        r = "8U";
        break;
    case CV_8S:
        r = "8S";
        break;
    case CV_16U:
        r = "16U";
        break;
    case CV_16S:
        r = "16S";
        break;
    case CV_32S:
        r = "32S";
        break;
    case CV_32F:
        r = "32F";
        break;
    case CV_64F:
        r = "64F";
        break;
    default:
        r = "User";
        break;
    }

    r += "C";
    r += (chanels + '0');

    return r;
}

QString hashCvMat(const cv::Mat &mat) {
    if (mat.empty()) {
        return QString{};
    }

    QByteArray matArray{reinterpret_cast<char *>(mat.data),
                        static_cast<qsizetype>(mat.total() * mat.elemSize())};

    QCryptographicHash hasher(QCryptographicHash::Md5);
    hasher.addData(matArray);

    return {hasher.result().toHex()};
}

QImage cvMatToQImage(const cv::Mat &mat) {
    switch (const auto matType = mat.type()) {
    case CV_8UC1:
        return QImage(mat.data, mat.cols, mat.rows, mat.step,
                      QImage::Format_Grayscale8);
    case CV_8UC3:
        return QImage(mat.data, mat.cols, mat.rows, mat.step,
                      QImage::Format_RGB888);
    case CV_8UC4:
        return QImage(mat.data, mat.cols, mat.rows, mat.step,
                      QImage::Format_RGBA8888);
    default:
        std::println(std::cerr,
                     "Unsupported format for conversion to QImage. Format: {}",
                     matTypeToString(matType));
        return QImage();
    }
}

cv::Mat convertToRGB(const cv::Mat &mat) {
    cv::Mat convertedMat;

    switch (const auto matType = mat.type()) {
    case CV_8UC1: {
        convertedMat = mat.clone();
        break;
    }
    case CV_8UC3:
        cv::cvtColor(mat, convertedMat, cv::COLOR_BGR2RGB);
        break;
    case CV_8UC4: {
        cv::cvtColor(mat, convertedMat, cv::COLOR_BGRA2RGBA);
        break;
    }
    case CV_32FC1: {
        double minValue, maxValue;
        cv::minMaxLoc(mat, &minValue,
                      &maxValue); // Find minimum and maximum values

        cv::Mat normalizedMat;
        mat.convertTo(normalizedMat, CV_32F, 255.0 / (maxValue - minValue),
                      -minValue * 255.0 / (maxValue - minValue));

        normalizedMat.convertTo(convertedMat, CV_8UC1);
        mat.convertTo(convertedMat, CV_8UC1);
    }
    case CV_32SC1: {
        double minValue, maxValue;
        cv::minMaxLoc(mat, &minValue, &maxValue);

        cv::Mat normalizedMat;
        mat.convertTo(normalizedMat, CV_32F, 255.0 / (maxValue - minValue),
                      -minValue * 255.0 / (maxValue - minValue));

        normalizedMat.convertTo(convertedMat, CV_8UC1);
        mat.convertTo(convertedMat, CV_8UC1);
        break;
    }

    default:
        std::println(std::cerr,
                     "Unsupported format for conversion to RGB. Format: {}",
                     matTypeToString(matType));
        break;
    }

    return convertedMat;
}
} // namespace

ImageModel::ImageModel(QObject *parent) : QAbstractListModel(parent) {}

int ImageModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;

    std::lock_guard lock{imageInfosMutex_};

    return imageInfos_.size();
}

QVariant ImageModel::data(const QModelIndex &index, int role) const {
    std::lock_guard lock{imageInfosMutex_};

    if (!index.isValid() || index.row() >= imageInfos_.size()) {
        return QVariant();
    }

    const auto &[imageInfo, imageInfoId] = imageInfos_.at(index.row());

    switch (role) {
    case IdRole:
        return imageInfoId;
    case TitleRole:
        return QString::fromStdString(imageInfo.title);
    case ImageRole:
        return QPixmap::fromImage(cvMatToQImage(imageInfo.image));
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ImageModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[TitleRole] = "title";
    roles[ImageRole] = "image";

    return roles;
}

void ImageModel::appendImages(std::vector<ImageInfo> imageInfos) {
    if (imageInfos.empty()) {
        return;
    }

    std::lock_guard lock{imageInfosMutex_};

    const int startRow = imageInfos_.size();
    int endRow = startRow + imageInfos.size() - 1;

    beginInsertRows(this->index(startRow), startRow, endRow);
    // beginResetModel();

    const auto imageInfosCount = imageInfos_.size() + imageInfos.size();
    imageInfos_.reserve(imageInfosCount);
    imageInfosIds_.reserve(imageInfosCount);

    for (size_t imageInfoIndex{0}; imageInfoIndex < imageInfos.size();
         ++imageInfoIndex) {
        auto &imageInfo = imageInfos.at(imageInfoIndex);
        imageInfo.image = convertToRGB(imageInfo.image);
        const auto imageId = hashCvMat(imageInfo.image);
        imageInfos_.emplace_back(std::move(imageInfo), imageId);
        imageInfosIds_.insert(std::move(imageId), imageInfos_.size() - 1);
    }

    // endResetModel();
    endInsertRows();
}

QPixmap ImageModel::getImage(const QString &imageId) const {
    if (const auto imageInfoIdIter = imageInfosIds_.find(imageId);
        imageInfoIdIter != imageInfosIds_.end()) {
        const auto imageInfoIndex = imageInfoIdIter.value();
        const auto &[imageInfo, imageInfoId] = imageInfos_.at(imageInfoIndex);

        return QPixmap::fromImage(cvMatToQImage(imageInfo.image));
    }

    return {};
}
