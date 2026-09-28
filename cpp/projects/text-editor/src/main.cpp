#include<iostream>
#include "Buffer.h"
#include "InsertCommand.h"
#include "DeleteCommand.h"

int main() {
    Buffer b;

    InsertCommand c1("Hello");
    c1.execute(b);
    std::cout << "[" << b.getText() << "]" << std::endl;

    DeleteCommand d1(3);
    d1.execute(b);
    std::cout << "[" << b.getText() << "]" << std::endl;

    d1.undo(b);
    std::cout << "[" << b.getText() << "]" << std::endl;

    c1.undo(b);
    std::cout << "[" << b.getText() << "]" << std::endl;

    return 0;
}