#pragma once
#include <string>
#include "Buffer.h"
#include "Command.h"

class InsertCommand : public Command{
    std::string text;

public:
    InsertCommand(const std::string& s);
    void execute(Buffer& b) override;
    void undo(Buffer& b) override;
};