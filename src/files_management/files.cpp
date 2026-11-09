#include "files_management/files.h"

int CreateFile(const char* path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to remove file \"" << path << "\".\n";
        return 1;
    }
    return 0;
}

int DeleteFile(const char* path) {
    if (remove(path) != 0) {
        std::cerr << "Failed to remove file \"" << path << "\".\n";
        return 1;
    }
    return 0;
}

int MoveFile(const char* path, const char* destPath) {
    if (rename(path, destPath) != 0) {
        std::cerr << "Failed to move/rename file\n";
        return 1;
    }
    return 0;
}

int CopyFile(const char* src, const char* dest) {
    std::ifstream source(src, std::ios::binary);
    std::ofstream destination(dest, std::ios::binary);

    if (!source.is_open()) {
        std::cerr << "Failed to open file \"" << src << "\".\n";
        return 1;
    }
    if (!destination.is_open()) {
        std::cerr << "Failed to open/create file \"" << dest << "\".";
        return 1;
    }

    destination << source.rdbuf();

    return 0;
}

int LoadFileToString(const char* path, std::string& fileData) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        std::cerr << "Failed to open file \"" << path << "\".\n";
        return 1;
    }

    std::streamsize fileLen = file.tellg();
    if (fileLen < 0) {
        std::cerr << "Failed to determine size of file \"" << path << "\".\n";
        return 1;
    }

    fileData.resize(static_cast<std::size_t>(fileLen));
    file.seekg(0);
    if (!file.read(fileData.data(), fileLen)) {
        std::cerr << "Failed to read file \"" << path << "\".\n";
        return 1;
    }

    return 0;
}

int ExportStringToFile(const char* path, std::string& fileData) {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cout << "Failed to open file\n";
        return 1;
    }

    file << fileData;

    return 0;
}

int AddStringToFile(const char* path, std::string& data) {
    std::ofstream file;
    file.open(path, std::ios::app);
    if (!file.is_open()) {
        std::cout << "Failed to open file\n";
        return 1;
    }
    file << data;

    return 0;
}