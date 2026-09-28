# C++ Mastery · Lesson 3 — const Correctness

`const` = a big marker of SENIOR C++. It makes code protect itself from mistakes.

## Basic: const = "this cannot change"
```cpp
const int x = 10;
x = 20;   // ❌ COMPILE ERROR — promised not to change x
```
A PROMISE to the compiler. Turns a potential runtime bug into a compile-time error → caught early.

## ★★ const reference — the idiomatic way to pass big read-only data ★★
Want NO copy (fast) AND can't-modify (safe)? → `const T&`.
```cpp
void printVector(const vector<int>& v) {   // reference to a vector I promise not to change
    for (int x : v) cout << x << " ";       // read = fine (no copy made)
    // v.push_back(5);  ❌ compile error — v is const
}
```
Best of both worlds: `&` = no copy even for a million elements; `const` = can't accidentally modify.
**Senior default for any non-trivial param you only READ: `const T&`.** (const vector<int>&, const string&…)

## Parameter decision rule (senior habit)
Ask: "do I need to modify the caller's data?"
| Situation                          | Pass as                | Why                          |
|------------------------------------|------------------------|------------------------------|
| small value (int/char/bool)        | by value `int x`       | copy is cheap, simplest      |
| big object, need to MODIFY it       | reference `vector<int>&`     | no copy + change original |
| big object, only READ it            | const ref `const vector<int>&` | no copy + protected     |

## ★ Pass-by-value modifies the COPY, not the caller's original
```cpp
void funcA(vector<int> data) { data.push_back(99); }  // changes ITS COPY only
// caller's vector is UNTOUCHED — copy is thrown away on return.
```
| Signature                    | Copies? | Modifies caller's original? |
|------------------------------|---------|------------------------------|
| `vector<int> data`           | yes     | NO (only its private copy)   |
| `vector<int>& data`          | no      | yes                          |
| `const vector<int>& data`    | no      | no                           |
Same lesson as addTenByValue: pass-by-value = a private copy; scribbles die on return.

## Also exists (preview, deeper later)
- pointer-to-const vs const-pointer: `const int* p` (can't change the value) vs `int* const p`
  (can't repoint). Read right-to-left.
- const MEMBER FUNCTIONS: `int size() const` — promises not to modify the object. (with classes)
