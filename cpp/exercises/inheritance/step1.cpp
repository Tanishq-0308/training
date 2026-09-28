#include <iostream>
using namespace std;

class Command {
public:
    virtual void hello() { cout << "Hello from command" << endl;}
};

class InheritClass : public Command { 
public:
    void hello () override {
        cout << "Hello from InheritClass" << endl;
    }
};

int main() {
    InheritClass h;
    h.hello();

    Command x;
    x.hello();

    Command& ref = h;
    ref.hello();

    Command& r2 = x;
    r2.hello();
}