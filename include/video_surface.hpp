#ifndef QT_STREAMING_VIDEO_SURFACE_HPP
#define QT_STREAMING_VIDEO_SURFACE_HPP

#include <QAbstractVideoSurface>
#include <QObject>
#include <QVideoSurfaceFormat>

class VideoSurface : public QObject {
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE
    setVideoSurface NOTIFY videoSurfaceChanged)

public:
    explicit VideoSurface();
    [[nodiscard]] QAbstractVideoSurface *videoSurface() const { return surface_.get(); }

public:
    void setVideoSurface(QAbstractVideoSurface *surface);
    void setFormat(int width, int height, QVideoFrame::PixelFormat frameFormat);

    public slots:
    void setFrame(const QVideoFrame &frame);

    signals:
    void videoSurfaceChanged();

private:
    QScopedPointer<QAbstractVideoSurface> surface_;
    QVideoSurfaceFormat format_;
};

#endif //QT_STREAMING_VIDEO_SURFACE_HPP
