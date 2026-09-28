#pragma once
#include "Buffer.h"
#include <string>
#include "Command.h"

class DeleteCommand : public Command {
    int count;
    std::string deletedText;

public:
    DeleteCommand(int deleteCount);
    void execute(Buffer& b) override;
    void undo(Buffer& b) override;
};