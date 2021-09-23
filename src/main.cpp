#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <camera.hpp>
#include <video_surface.hpp>

constexpr auto mainPanelName = "mainPanel";
constexpr auto videoSurfaceName = "display";

static QPointer<VideoSurface> getSurfaceElement(QPointer<QObject> rootObject) {
    QPointer<QObject> display(
            rootObject->findChild<QObject *>(mainPanelName)
                    ->findChild<QObject *>(videoSurfaceName));
    QPointer<VideoSurface> surface{qvariant_cast<VideoSurface *>(display->property("source"))};
    return surface;
}

int main(int argc, char *argv[]) {
    QGuiApplication a(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<VideoSurface>("com.streaming.FrameProvider", 1, 0,
                                  "FrameProvider");

    engine.load(QUrl("qrc:/main.qml"));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    QPointer<QObject> root(engine.rootObjects().first());

    auto surface = getSurfaceElement(root);
    root.clear();

    Camera camera;
    camera.start(surface);

    QObject::connect(&a, &QGuiApplication::aboutToQuit, [&surface](){
        surface.clear();
    });

    return QGuiApplication::exec();
}
