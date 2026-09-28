#pragma once
#include <string>
#include "Buffer.h"

class Command {

public:
    virtual void execute(Buffer& b) = 0;
    virtual void undo(Buffer& b) = 0;
    virtual ~Command() {}
};
