#include "Buffer.h"

void Buffer::insert(const std::string& s) {
    text += s;
}

void Buffer::remove(int n) {
    if (n <= 0) return;
    if (n > (int)text.size()) n = text.size();
    text.erase(text.size() - n);
}

const std::string& Buffer::getText() const {
    return text;
}

int Buffer::size() const {
    return text.size();
}
