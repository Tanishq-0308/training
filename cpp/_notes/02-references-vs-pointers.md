# C++ Mastery · Lesson 2 — References (vs Pointers)

## What a reference is
An **alias** — another NAME for an existing variable. Not a copy, not a pointer. Same memory, two names.
```cpp
int x = 10;
int& ref = x;   // int& = "reference to int". ref IS x.
ref = 20;       // changes x too → they're the SAME variable
```
Analogy: a nickname. "Adi" and "Aditya" = same person; dress one, you dressed both.

## Pointer vs Reference (THE interview comparison)
```cpp
int x = 10;
int* p = &x;   // POINTER: holds x's ADDRESS. Use * to access value: *p = 20;
int& r = x;    // REFERENCE: an ALIAS. Use directly: r = 20;
```
|                     | Pointer `int* p`        | Reference `int& r`        |
|---------------------|-------------------------|---------------------------|
| what it is          | holds an ADDRESS        | an ALIAS (another name)   |
| access value        | needs `*` (dereference) | used DIRECTLY             |
| can be null?        | yes (nullptr)           | NO — always aliases sth   |
| can be reseated?    | yes (point elsewhere)   | NO — bound for life       |
| must init at decl?  | no                      | YES                       |

**3 key facts:** reference (1) can't be null, (2) can't be reseated, (3) used directly (clean syntax).

## ★ THE trap: `r = b` does NOT reseat r
```cpp
int a = 5; int& r = a; int b = 10;
r = b;   // r can't be reseated → this ASSIGNS b's value into a → a = 10
// output: a=10, r=10, b=10
```
Rule: **assignment through a reference always goes to the ALIASED variable's VALUE.**
You can never change WHAT it aliases, only the value of what it aliases.
(Contrast: `p = &b` genuinely reseats a POINTER to point at b.)

## ★★ Why references matter in practice: avoid COPYING (this is the vector<int>& in DSA!)
Pass by VALUE → C++ copies the whole thing:
```cpp
void foo(vector<int> v)   // ❌ copies the ENTIRE vector (slow for big data)
```
Pass by REFERENCE → no copy, works on the original:
```cpp
void foo(vector<int>& v)  // ✅ v is an alias to caller's vector — zero copy
```
A million-element vector: by-value copies all million; by-reference copies nothing.
→ THIS is why every DSA function used `vector<int>&`. Was using references all along.

## Ownership note (foreshadows smart pointers)
A function returning `new`'d heap memory (`int* f(){ return new int(5); }`) is SAFE but transfers
OWNERSHIP — the caller must `delete` it or it leaks. Fragile. → smart pointers (unique_ptr) fix this.
