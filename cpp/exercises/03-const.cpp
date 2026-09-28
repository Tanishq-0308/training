#include <iostream>
#include <vector>
using namespace std;

// A function that only READS the vector → should take it by CONST REFERENCE.
// TASK A: write printAll(const vector<int>& v) that prints each element.
//   void printAll(const vector<int>& v) { for (int x : v) cout << x << " "; cout << endl; }
void printAll(const vector<int>& v) {
    for (int x: v) {
        cout << x << " ";
        cout << endl;
    }
}

// A function that MODIFIES the vector → takes a plain (non-const) REFERENCE.
// TASK B: write addOne(vector<int>& v) that adds 1 to every element.
//   void addOne(vector<int>& v) { for (int& x : v) x++; }   // note: int& to modify in place!
void addOne(vector<int>& v) {
    for (int& x : v) {
        x += 1;
    }
}

int main() {
    vector<int> nums = {1, 2, 3};

    // TASK A test:
    printAll(nums);          // expect: 1 2 3

    // TASK B test:
    addOne(nums);
    printAll(nums);          // expect: 2 3 4

    // TASK C (the const demo): after writing printAll, try ADDING this line INSIDE printAll:
    //     v.push_back(99);
    //   then compile. It should FAIL. Read the error, then remove the line.
    //   (This proves const protects the data.)

    return 0;
}
