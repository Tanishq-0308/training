// C++ Lesson 8 — Templates
//
// TASK 1: Write a template function `maxOf` that returns the larger of two values,
//         and works for int, double, and string.
//
// TASK 2: Write a template function `printAll` that takes a vector of ANY type
//         and prints every element separated by a space, then a newline.
//         (Pass it the senior way — see Lesson 3.)
//
// Write the #includes and both functions yourself. main() is already written.

// ... your includes here ...

// ... your maxOf template here ...

// ... your printAll template here ...
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <typename T>
void printAll(const vector<T>& value) {
    for (const T& i : value) {   // const T& not T — avoids copying each element
        cout << i << " ";
    }
    cout << endl;
}

template <typename T>
T maxOf(T a,T b) {
    return (a > b) ? a : b;
}

int main() {
    // TASK 1
    cout << maxOf(3, 7) << endl;                      // 7
    cout << maxOf(2.5, 1.5) << endl;                  // 2.5
    cout << maxOf(string("apple"), string("zebra")) << endl;  // zebra

    // TASK 2
    vector<int> nums = {1, 2, 3};
    vector<string> words = {"hello", "world"};
    printAll(nums);    // 1 2 3
    printAll(words);   // hello world

    return 0;
}
