//
// Created by jonsnow on 07/02/22.
//

#include "imutils/paths.hpp"

#include <filesystem>
#include <algorithm>
#include <vector>

namespace fs = std::filesystem;

/**
* @var imageTypes
* @brief contains all types of image extensions supported by Opencv
**/
std::vector<std::string> imageTypes = {".jpg", ".jpeg", ".png", ".bmp", ".tif", ".tiff"};

std::vector<std::string> imutils::listImages(const std::filesystem::path& basePath, const std::string& contains) {
    return listFiles(basePath, imageTypes, contains);
}

std::vector<std::string> imutils::listFiles(const std::filesystem::path& basePath,const std::vector<std::string>& validExts,const std::string& contains) {
    std::vector<std::string> filesDirs;

    for (const auto& dirEntry : fs::recursive_directory_iterator(basePath)) {
        std::filesystem::path file = dirEntry.path();
        if (contains != "" and (file.filename().string()).find(contains) == std::string::npos)
            continue;
        if (validExts.empty())
            filesDirs.push_back(dirEntry.path().string());
        else if (std::find(validExts.begin(), validExts.end(), file.extension()) != validExts.end())
            filesDirs.push_back(dirEntry.path().string());
    }
    return filesDirs;
}