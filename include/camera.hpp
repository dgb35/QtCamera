#ifndef QT_STREAMING_CAMERA_HPP
#define QT_STREAMING_CAMERA_HPP

#include <QObject>
#include <QCamera>
#include <QVideoProbe>
#include <QPointer>

#include <memory>

#include "video_surface.hpp"

class Camera : public QObject {
Q_OBJECT
public:
    explicit Camera(QPointer<VideoSurface> videoSurface, QObject *parent = nullptr);
    ~Camera() override;

public slots:
    void start();
    void stop();

signals:
    void stateChanged(QCamera::State);

protected:
    std::unique_ptr<QCamera> _camera;
    std::unique_ptr<QVideoProbe> _probe;

    QPointer<VideoSurface> _videoSurface;
};


#endif //QT_STREAMING_CAMERA_HPP
