#include "files_management/files.h"

int CreateFile(const char* path) {
    ofstream file(path);
    if (!file.is_open()) {
        cerr << "Failed to remove file \"" << path << "\".\n";
        return 1;
    }
    return 0;
}

int DeleteFile(const char* path) {
    if (remove(path) != 0) {
        cerr << "Failed to remove file \"" << path << "\".\n";
        return 1;
    }
    return 0;
}

int MoveFile(const char* path, const char* destPath) {
    if (rename(path, destPath) != 0) {
        cerr << "Failed to move/rename file\n";
        return 1;
    }
    return 0;
}

int CopyFile(const char* src, const char* dest) {
    ifstream source(src, ios::binary);
    ofstream destination(dest, ios::binary);

    if (!source.is_open()) {
        cerr << "Failed to open file \"" << src << "\".\n";
        return 1;
    }
    if (!destination.is_open()) {
        cerr << "Failed to open/create file \"" << dest << "\".";
        return 1;
    }

    destination << source.rdbuf();

    return 0;
}

int LoadFileToString(const char* path, string& fileData) {
    ifstream file(path, ios::binary | ios::ate);

    if (!file.is_open()) {
        cerr << "Failed to open file \"" << path << "\".\n";
        return 1;
    }

    streamsize fileLen = file.tellg();
    if (fileLen < 0) {
        cerr << "Failed to determine size of file \"" << path << "\".\n";
        return 1;
    }

    fileData.resize(static_cast<size_t>(fileLen));
    file.seekg(0);
    if (!file.read(fileData.data(), fileLen)) {
        cerr << "Failed to read file \"" << path << "\".\n";
        return 1;
    }

    return 0;
}

int ExportStringToFile(const char* path, string& fileData) {
    ofstream file(path);
    if (!file.is_open()) {
        cout << "Failed to open file\n";
        return 1;
    }

    file << fileData;

    return 0;
}

int AddStringToFile(const char* path, string& data) {
    ofstream file;
    file.open(path, ios::app);
    if (!file.is_open()) {
        cout << "Failed to open file\n";
        return 1;
    }
    file << data;

    return 0;
}