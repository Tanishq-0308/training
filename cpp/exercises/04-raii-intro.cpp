#include <iostream>
using namespace std;

// A class that OWNS a heap int: allocates in ctor, frees in dtor.
// This is RAII — the destructor guarantees cleanup, so no manual delete needed.
class IntBox {
public:
    int* data;

    // TASK A: constructor — take an int `value`, allocate it on the HEAP (new), store in data.
    //   IntBox(int value) { data = new int(value); cout << "allocated " << value << endl; }
    IntBox(int value) {
        data = new int(value);
        cout << "allocated" << value << endl;
    }

    // TASK B: destructor — free the heap memory, and print "freed".
    //   ~IntBox() { delete data; cout << "freed" << endl; }
    ~IntBox() {
        delete data;
        cout << "freed" << endl;
    }

};

int main() {
    cout << "start" << endl;
    {
        IntBox box(42);
        cout << "value = " << *box.data << endl;   // dereference: 42
    }   // ← box goes out of scope here → destructor runs → memory auto-freed
    cout << "end" << endl;
    return 0;
}
