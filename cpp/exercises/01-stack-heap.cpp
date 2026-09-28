#include <iostream>
using namespace std;

int* makeCOunter() {
    int* x = new int(5);
    return x;
}


int main() {
    int n;
    cout << "Enter a number :" << endl;
    cin >> n;
    cout << "heello: "<<  n << endl;
    // int arr[n];
    // cout << sizeof(arr) << endl;
    // ── PART 1: a stack variable ──
    // int stackVar = 10;
    // cout << "stackVar value: " << stackVar << endl;
    // cout << "stackVar address: " << &stackVar << endl;   // &x = "address of x"

    // // ── PART 2: a heap variable ──
    // // TASK A: allocate an int on the HEAP with value 20, using `new`.
    // //   syntax:  int* heapVar = new int(20);
    // int* heapVar = new int(20);


    // // TASK B: print the VALUE the pointer points to.
    // //   To get the value a pointer points to, you DEREFERENCE it with *:  *heapVar
    // //   cout << "heapVar value: " << *heapVar << endl;
    // cout << "heapVar value: " << *heapVar << endl;


    // // TASK C: print the pointer itself (heapVar) — that's the HEAP address it holds.
    // //   cout << "heapVar (the address it points to): " << heapVar << endl;
    // cout << "heapVar (the address it points to): " << heapVar << endl;

    // // TASK D: also print &heapVar — the STACK address where the POINTER itself lives.
    // //   (This proves: the pointer is on the stack, the value is on the heap — different addresses.)
    // //   cout << "&heapVar (where the pointer lives): " << &heapVar << endl;
    // cout << "&heapVar (where the pointer lives): " << &heapVar << endl;


    // // TASK E: free the heap memory (every new needs a delete!)
    // //   delete heapVar;
    // delete heapVar;


    return 0;
}
