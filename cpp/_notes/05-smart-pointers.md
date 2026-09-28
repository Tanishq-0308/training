# C++ Mastery · Lesson 5 — Smart Pointers

RAII applied to pointers, pre-built by the stdlib. Modern C++: never write raw new/delete.
`#include <memory>`

## The problem: raw pointers are dangerous
`int* p = new int(42); ... delete p;` → forget = leak; exception before delete = leak;
delete twice = crash. Smart pointers = your IntBox RAII idea, generic and built-in.

## unique_ptr — the DEFAULT (one owner)
```cpp
unique_ptr<int> p = make_unique<int>(42);  // heap int(42); make_unique replaces raw `new`
cout << *p;                                 // dereference like normal → 42
// auto-deletes when p leaves scope. No delete. Leak-proof, exception-safe.
```
★ **Cannot be COPIED** — enforces exactly ONE owner → prevents double-delete.
```cpp
unique_ptr<int> b = a;   // ❌ compile error: "use of deleted function ...unique_ptr(const&)"
```
(Ownership can be MOVED with std::move — later lesson — but never copied.)

## shared_ptr — multiple owners (ref-counted)
```cpp
shared_ptr<int> a = make_shared<int>(42);
shared_ptr<int> b = a;   // ✅ OK — 2 owners, same int
// freed only when the LAST owner is gone (ref count hits 0).
```
Keeps a REFERENCE COUNT: +1 per copy, -1 per destruction; free at 0. (Like a shared Google
Doc: exists while someone has it open; deleted when everyone closes it.) Has ref-count overhead.

## Decision rule
| Need                          | Use          |
|-------------------------------|--------------|
| one owner (common)            | unique_ptr (default, zero overhead) |
| genuinely shared ownership    | shared_ptr (ref-count cost)         |
| just borrowing, not owning    | raw pointer / reference (don't own) |

**Modern/senior C++: never raw new/delete. Use make_unique / make_shared.** RAII → automatic,
leak-proof, exception-safe.
