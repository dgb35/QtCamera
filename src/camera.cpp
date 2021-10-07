#include <camera.hpp>

#include <memory>
#include <utility>

Camera::Camera(QPointer<VideoSurface> videoSurface, QObject *parent) : QObject(parent), _camera{nullptr}, _probe{nullptr}, _videoSurface{std::move(videoSurface)} {
    _camera = std::make_unique<QCamera>();
    _probe = std::make_unique<QVideoProbe>();

    _camera->setCaptureMode(QCamera::CaptureMode::CaptureVideo);

    QCameraViewfinderSettings settings;
    settings.setResolution(640, 480);
    settings.setMaximumFrameRate(30);
    settings.setPixelFormat(QVideoFrame::Format_Jpeg);
    _camera->setViewfinderSettings(settings);

    _probe->setSource(_camera.get());
    QObject::connect(_probe.get(), &QVideoProbe::videoFrameProbed, _videoSurface, &VideoSurface::setFrame,
                     Qt::QueuedConnection);

    connect(_camera.get(), &QCamera::stateChanged, this, &Camera::stateChanged);
}

void Camera::start() {
    if (_camera->state() != QCamera::ActiveState)
        _camera->start();
}

void Camera::stop() {
    if (_camera->state() == QCamera::ActiveState)
        _camera->stop();
}

Camera::~Camera() {
    stop();
    _camera.reset(nullptr);
    _probe.reset(nullptr);
}
