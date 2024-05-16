#include "image_info.hpp"
#include "qt/ImageLoader.hpp"
#include "qt/ImageModel.hpp"
#include "qt/ImageProvider.hpp"
#include "qt/VideoItem.hpp"

#include <opencv2/opencv.hpp>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickImageProvider>
#include <QUrl>

#include <vector>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<VideoItem>("VideoComponents", 1, 0, "VideoItem");

    QQmlApplicationEngine engine;

    ImageModel imageModel;
    ImageLoader imageLoader;

    imageLoader.addImageInfosAddedCallback(
        [&imageModel](std::vector<ImageInfo> imageInfos) {
            imageModel.appendImages(std::move(imageInfos));
        });
    std::jthread imageLoaderThread([&imageLoader] { imageLoader.load(); });

    engine.rootContext()->setContextProperty("imageModel", &imageModel);
    auto imageProvider = new ImageProvider{&imageModel};
    engine.addImageProvider(QLatin1String{"pixmaps"}, imageProvider);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
