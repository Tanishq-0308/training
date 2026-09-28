#pragma once
#include <string>

// The document itself. Holds text; knows nothing about undo.
class Buffer {
    std::string text;

public:
    void insert(const std::string& s);
    void remove(int n);
    const std::string& getText() const;
    int size() const;
};
