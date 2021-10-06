#include <video_surface.hpp>

#include <chrono>
#include <iostream>

#include <QDebug>

VideoSurface::VideoSurface() : surface_{nullptr} {}

void VideoSurface::setVideoSurface(QAbstractVideoSurface *surface) {
    if (surface_.get() && surface_.get() != surface && surface_->isActive()) {
        surface_->stop();
    }
    surface_.reset(surface);

    if (surface_.get()) {
        format_ = surface_->nearestFormat(format_);
        surface_->start(format_);
    }
}

void VideoSurface::setFormat(int width, int height,
                             QVideoFrame::PixelFormat format) {
    QSize size(width, height);
    QVideoSurfaceFormat surfaceFormat(size, format);
    format_ = surfaceFormat;

    if (surface_.get()) {
        if (surface_->isActive()) {
            surface_->stop();
        }
        format_ = surface_->nearestFormat(format_);
        surface_->start(format_);
    }
}

void VideoSurface::setFrame(const QVideoFrame &frame) {
    if (surface_.get()) {
//        auto start = std::chrono::system_clock::now();
        auto f(frame);
        f.map(QAbstractVideoBuffer::ReadOnly);
        setFormat(f.width(), f.height(), QVideoFrame::pixelFormatFromImageFormat(f.image().format()));
        surface_->present(f.image());
        f.unmap();
//        auto end = std::chrono::system_clock::now();
//        std::cout << "Frame time: " << std::chrono::duration_cast<std::chrono::milliseconds>((end - start)).count()
//                  << "ms" << std::endl;
    }
}
