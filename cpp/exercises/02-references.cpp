#include <iostream>
using namespace std;

// ── PART 1: pass by VALUE — makes a COPY, original is NOT changed ──
void addTenByValue(int x) {
    x = x + 10;   // changes only the local COPY
}

// ── PART 2: pass by REFERENCE — works on the ORIGINAL ──
// TASK A: write addTenByReference that takes an int BY REFERENCE (int&)
//         and adds 10 to it. Because it's a reference, it changes the caller's variable.
//   void addTenByReference(int& x) { x = x + 10; }
void addTenByReference(int& x) {
    x += 10;
}


// ── PART 3: the classic "swap" — impossible cleanly WITHOUT references/pointers ──
// TASK B: write swap(int& a, int& b) that swaps the two values using a temp variable.
//   (This is THE textbook example of why references exist.)
//   void swap(int& a, int& b) { int temp = a; a = b; b = temp; }
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b =temp;
}


int main() {
    int n = 5;

    addTenByValue(n);
    cout << "after addTenByValue: " << n << endl;      // still 5 (copy was changed)

    // TASK A test — uncomment once you've written addTenByReference:
    addTenByReference(n);
    cout << "after addTenByReference: " << n << endl; // now 15 (original changed)

    // TASK B test — uncomment once you've written swap:
    int p = 1, q = 2;
    swap(p, q);
    cout << "after swap: p=" << p << " q=" << q << endl;  // p=2 q=1

    return 0;
}
