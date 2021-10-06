#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <camera.hpp>
#include <video_surface.hpp>
#include <images.hpp>
#include <random>

constexpr auto videoSurfaceName = "display";

static QPointer<VideoSurface> getSurfaceElement(QPointer<QObject> rootObject) {
    QPointer<QObject> display(rootObject->findChild<QObject *>(videoSurfaceName, Qt::FindChildrenRecursively));
    QPointer<VideoSurface> surface{qvariant_cast<VideoSurface *>(display->property("source"))};
    return surface;
}

int main(int argc, char *argv[]) {
    std::random_device rd;
    std::mt19937 mersenne(rd());

    QGuiApplication a(argc, argv);

    ImageStorage storage;
    storage.loadImages(R"(../qml/images)");

    QQmlApplicationEngine engine;

    qmlRegisterType<VideoSurface>("com.streaming.FrameProvider", 1, 0,
                                  "FrameProvider");

    engine.load(QUrl("qrc:/main.qml"));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    QPointer<QObject> root(engine.rootObjects().first());
    auto surface = getSurfaceElement(root);
    QObject::connect(&a, &QGuiApplication::aboutToQuit, [&surface]() {
        surface.clear();
    });
    root.clear();

    Camera camera(surface);
    engine.rootContext()->setContextProperty("camera", &camera);

    QObject::connect(&camera, &Camera::stateChanged, [&storage, &surface, &mersenne](QCamera::State state) {
        if(state != QCamera::ActiveState)
            surface->setFrame(storage.images[static_cast<int>(mersenne() % storage.images.size())]);
    });

    return QGuiApplication::exec();
}
