# C++ Mastery · Lesson 6 — Move Semantics (std::move)

Performance: TRANSFER resources instead of COPYING them.

## Copy vs Move
- **Copy** = duplicate everything. Source keeps its data, dest gets an identical copy. Expensive.
- **Move** = steal the internals. Dest takes source's guts; source left empty. Cheap (pointer swaps).
- Analogy: copy = photocopy 500 pages; move = hand over the document.

## std::move — "I'm done with this, you may steal it"
```cpp
vector<int> a = {1,2,3};
vector<int> b = std::move(a);   // b takes a's data, a is now empty (valid but moved-from)
```
std::move doesn't move anything itself — it just MARKS a as OK-to-steal.

## ★ The unique_ptr answer (can't copy, but CAN move)
```cpp
unique_ptr<int> a = make_unique<int>(42);
unique_ptr<int> b = std::move(a);   // ✅ ownership transfers: a -> nullptr, b owns 42
```
- COPY a unique_ptr = forbidden (2 owners = double-delete). MOVE = allowed (ownership hands over,
  still exactly ONE owner). This is HOW you transfer a unique_ptr — NOT by switching to shared_ptr.

## lvalue vs rvalue (light)
- lvalue = has a name, reusable (`a`, `x`). rvalue = temporary, disposable (`5`, `a+b`, a return value).
- rvalues are safe to steal from (nobody uses them again). std::move casts an lvalue to "treat as rvalue".
