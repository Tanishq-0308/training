#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(int deleteCount) {
    count = deleteCount;
}

void DeleteCommand::execute(Buffer& b) {
    if (count > (int)b.getText().size()) count = b.getText().size();
    deletedText = b.getText().substr(b.getText().size() - count);
    b.remove(count);
}

void DeleteCommand::undo(Buffer& b) {
    b.insert(deletedText);
}