# C++ Mastery · Lesson 1 — Memory Model (Stack vs Heap)

Everything senior in C++ (pointers, references, RAII, smart pointers, move) rests on this.

## The two regions

### Stack 📚 — automatic, fast, small
- Holds LOCAL variables inside functions.
- Works like a stack of plates: calling a function PUSHES a frame; returning POPS it.
- Variables are AUTOMATICALLY destroyed when the function returns.
- Fast (just move a pointer). Small (~1–8 MB). Overflow → "stack overflow" crash.
- Lifetime = automatic. You don't manage it.

### Heap 🗄️ — manual, slower, large
- Memory you request at runtime with `new`; stays until you `delete` it.
- Does NOT die when the function ends.
- Slower (system must find free space). Large (limited by RAM).
- Lifetime = MANUAL. You must free it. Forget → **memory leak**.

## Core mental model
**Stack = automatic, fast, small, dies with the function.**
**Heap  = manual, slower, large, lives until you free it.**

## ★★ THE key insight: a pointer and its target live in DIFFERENT places
```cpp
void baz() { int* p = new int(100); }
```
```
   STACK              HEAP
 ┌───────┐         ┌───────┐
 │   p   │ ──────▶ │  100  │
 └───────┘         └───────┘
 pointer            value
 (stack)            (heap)
```
- `p` (the pointer) lives on the STACK — a small box holding an ADDRESS.
- the `100` (made by `new`) lives on the HEAP.
- When baz() returns: `p` is destroyed (stack popped), but the `100` is NOT.

## MEMORY LEAK (the classic C++ bug)
If `p` was the only pointer to the heap memory and `p` dies → that heap memory is now
unreachable AND un-freeable → wasted for the program's whole life. That's a leak.
**Rule: every `new` must have a matching `delete`.**
```cpp
void baz() { int* p = new int(100); /* use */ delete p; }  // ✅ free before p dies
```

## ★ WHY use the heap at all? (stack is faster/auto — so heap only when stack CAN'T)
Three things the stack CANNOT do → the reasons to use the heap:
1. **Outlive the function.** Stack vars die on return. Returning `&localVar` = dangling pointer.
   Heap lives until you `delete` → can be returned/stored/shared.
2. **Size decided at RUNTIME.** Stack size must be known at COMPILE time (`int arr[n]` with runtime
   n is not standard). Heap: `new int[n]` allocates n at runtime. (This is what `vector` does inside.)
3. **Too big for the stack.** Stack is small (~1–8 MB) → huge arrays crash (stack overflow).
   Heap is large (GBs, limited by RAM).
**Rule of thumb: default to STACK (fast/safe/auto). Reach for HEAP only for lifetime / runtime-size /
large-data.** (These are exactly why vector, string, new exist.)

## Note: addresses change every run = ASLR (security)
Address Space Layout Randomization — OS loads the program at a RANDOM location each run, so
attackers can't guess addresses (defeats buffer-overflow exploits). So: absolute address VALUES
are meaningless/random; only the RELATIONSHIPS matter (stack addrs cluster; heap is far away).

## Why this matters (interview + foreshadowing)
- "memory leak" = heap memory never deleted.
- "dangling pointer" = pointer to memory that already died (e.g. stack var that went out of scope).
- "why vector > raw array" = vector manages heap FOR you.
- Manually matching new/delete is error-prone (forget, or exception skips delete) → that's WHY
  modern C++ has **smart pointers** (unique_ptr/shared_ptr) that delete automatically. (later lesson)
