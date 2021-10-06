#ifndef QT_STREAMING_IMAGES_HPP
#define QT_STREAMING_IMAGES_HPP

#include <iostream>
#include <filesystem>
#include <QString>
namespace fs = std::filesystem;

struct ImageStorage {
    void loadImages(const fs::path& path) {
        if (fs::exists(path)){
            QImage tmp;
            for (const auto& file : fs::recursive_directory_iterator(path)){
                if (tmp.load(QString(file.path().string().c_str()))){
                    images.push_back(tmp);
                }
                else {
                    std::cout << "Can't load file" << std::endl;
                }
            }
        }
        else {
            std::cout << "Directory doesn't exist" << std::endl;
        }
    }
    [[nodiscard]] QList<QImage> getImages() const {
        return images;
    }
    QList<QImage> images{};
};

#endif //QT_STREAMING_IMAGES_HPP
