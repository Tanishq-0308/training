#include "InsertCommand.h"

InsertCommand::InsertCommand(const std::string& s) {
    text = s;
}

void InsertCommand::execute(Buffer& b){
    b.insert(text);
}

void InsertCommand::undo(Buffer& b) {
    b.remove(text.size());
}