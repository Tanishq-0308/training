# C++ for DSA · Lesson 1–2 — Basics + vector

## Program skeleton (every DSA program)
```cpp
#include <iostream>
using namespace std;        // so we write cout not std::cout

int main() {                // execution ALWAYS starts in main()
    cout << "text" << endl; // print (= console.log). endl = newline.
    return 0;               // 0 = finished successfully
}
```
- `int main()` is mandatory — the entry point. Code lives in functions; main runs first.
- Every statement ends with `;` (NOT optional, unlike JS).
- `cout << x << endl;` prints. `<<` pushes things to output.

## Compile then run (C++ is COMPILED, JS is interpreted)
```
g++ file.cpp -o file     # 1. compile → catches errors here
./file                   # 2. run
```
The compile step is WHY C++ catches bugs (types etc.) before running.

## ⚠️⚠️ TYPE-SIZE BUG I HIT ON LEETCODE (Two Sum, 61/63 then WA)
Used `unordered_map<char, int>` to store NUMBER keys. A `char` holds only ~ -128..127 (1 byte).
Big numbers like 6142 OVERFLOW and wrap to garbage → corrupted map → wrong answer.
- Small test numbers fit a char → passed. Big-number test [1,6142,8192,10239] → failed.
- **RULE: the map's KEY TYPE must match the data.** Counting letters → `<char,int>`.
  Storing numbers → `<int, int>`. (I copied the char habit from the anagram problem — wrong here.)
- Deep lesson JS hides: C++ types have SIZE LIMITS; wrong type silently corrupts data.
  JS "a number is a number"; C++ you must pick int/long/etc. to fit your values.
- Also: ALWAYS test on the real judge — local small tests hid this; LeetCode's big-number case caught it.

## Types — every variable needs one (the big JS difference)
JS: `let x = 25` (can become anything). C++: a variable has a FIXED type.
| Type     | Holds          | Example               |
|----------|----------------|-----------------------|
| int      | whole numbers  | `int x = 5;`          |
| double   | decimals       | `double pi = 3.14;`   |
| char     | one character  | `char c = 'A';`       |
| bool     | true/false     | `bool ok = true;`     |
| string   | text           | `string s = "hi";` (needs <string>) |
- Print a variable: `cout << age << endl;` (NO quotes → prints value, not the word).

## vector = C++'s array (growable list)
```cpp
#include <vector>
vector<int> nums = {2, 7, 11, 15};  // "growable list of ints". <int> = element type.
```
| Need            | C++                 | JS equivalent     |
|-----------------|---------------------|-------------------|
| length          | `nums.size()`       | `nums.length`     |
| access index    | `nums[0]`           | `nums[0]`         |
| add to end      | `nums.push_back(9)` | `nums.push(9)`    |
| change element  | `nums[1] = 50`      | `nums[1] = 50`    |
- ALL elements must be the same type (the `<int>`). Want decimals → `vector<double>`.

## Loop over a vector (IDENTICAL to JS, just int i + .size())
```cpp
for (int i = 0; i < nums.size(); i++) {
    cout << nums[i] << endl;
}
```

## Key mindset
C++ for DSA = SAME logic as JS, slightly different syntax. The thinking transfers 100%;
only syntax (types, .size(), push_back, compile step) changes.
