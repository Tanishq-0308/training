#include <iostream>
#include <memory>
#include <vector>
using namespace std;

int main() {
    // TASK A: make unique_ptr<int> `a` holding 99. Move it into `b`. Then print:
    //   - whether a is nullptr  (a == nullptr)
    //   - *b
    // (expect: 1  then  99)
    unique_ptr<int> a = make_unique<int>(99);
    unique_ptr<int> b = move(a);

    cout << (a == nullptr) << " and " << *b << endl;


    // TASK B: make a vector<int> `v` = {1,2,3}. Move it into `w`.
    //   Print w.size() and v.size().  (w=3, v=0 after move — v is emptied)
    vector<int> v = {1,2,3};
    vector<int> w = move(v);

    cout << w.size() << " and " << v.size() << endl;

    return 0;
}
