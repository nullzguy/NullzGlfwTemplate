#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int CreateFile(const char* path);
int DeleteFile(const char* path);
int MoveFile(const char* path, const char* destPath);
int CopyFile(const char* path, const char* destPath);
int LoadFileToString(const char* path, string& fileData);
int ExportStringToFile(const char* path, string& fileData);
int AddStringToFile(const char* path, string& data);