#include "../include/camera.hpp"

#include <memory>

Camera::Camera(QObject *parent) : QObject(parent), _camera{nullptr}, _probe{nullptr}, _videoSurface{nullptr} {}

void Camera::start(QPointer<VideoSurface> videoSurface) {
    _camera = std::make_unique<QCamera>();
    _probe = std::make_unique<QVideoProbe>();

    _camera->setCaptureMode(QCamera::CaptureMode::CaptureVideo);

    QCameraViewfinderSettings settings;
    settings.setResolution(640, 480);
    settings.setMaximumFrameRate(30);
    settings.setPixelFormat(QVideoFrame::Format_Jpeg);
    _camera->setViewfinderSettings(settings);

    _probe->setSource(_camera.get());
    qDebug() << videoSurface->videoSurface();
    QObject::connect(_probe.get(), &QVideoProbe::videoFrameProbed, videoSurface, &VideoSurface::setFrame,
                     Qt::QueuedConnection);
    _camera->start();
}

Camera::~Camera() {
}

