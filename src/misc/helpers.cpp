#include "misc/helpers.h"

uint Read2xBu(std::string& str, int idx) {
    return (
        (str[idx+0] << 0  & 0x000000ff) |
        (str[idx+1] << 8  & 0x0000ff00)
    );
}

uint Read4xBu(std::string& str, int idx) {
    return (
        (str[idx+0] << 0  & 0x000000ff) |
        (str[idx+1] << 8  & 0x0000ff00) |
        (str[idx+2] << 16 & 0x00ff0000) |
        (str[idx+3] << 24 & 0xff000000)
    );
}

int SearchStrIdx(std::string& str, std::string& item) {
    int iters = str.length()-item.length()+1;
    for (int i = 0; i < iters; i++) {
        bool b = false;
        for (int j = 0; j < item.length(); j++) {
            if (str[i+j] != item[j]) {b = true; break;}
        }
        if (b) continue;
        return i;
    }
    return -1;
}