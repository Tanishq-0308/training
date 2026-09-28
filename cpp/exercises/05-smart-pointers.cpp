#include <iostream>
#include <memory>
using namespace std;

int main() {
    // TASK A: create a unique_ptr<int> holding 77 using make_unique, then print its value.
    //   (dereference with *)
    unique_ptr<int> it = make_unique<int>(77);
    cout << *it << endl;


    // TASK B: create a shared_ptr<int> `a` holding 10. Then make `b = a` (second owner).
    //   Print both *a and *b, and print a.use_count() (how many owners → should be 2).
    shared_ptr<int> a = make_shared<int>(10);
    shared_ptr<int> b = a;
    cout << *a << endl;
    cout << *b << endl;
    cout << "owners: " << b.use_count() << endl;

    return 0;
}
