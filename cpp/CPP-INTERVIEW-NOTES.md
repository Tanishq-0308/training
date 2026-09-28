# 📘 C++ — Combined Interview Notes

**One file. Everything I've learned. Revise from this before any interview.**

How to use this file:
- **🎤 SAY THIS** blocks = the exact words to speak in an interview. Read them aloud until they feel natural.
- **Q:** lines = the question an interviewer actually asks.
- ⚠️ = a gotcha that has bitten me or commonly bites people.
- Deep first-time explanations live in `_notes/` (one file per lesson). This file is for **revision**.

### ⛔ The rule that makes this file work
**Never revise by reading.** Reading feels like learning and isn't — the research calls this the *fluency illusion*.
Every section starts with a **🎯 CUE** box: read only that, answer out loud from memory, **then** scroll down and check.
Struggling and failing to recall is what encodes the memory. Getting it smoothly by reading encodes nothing.

Appended at the end of every session. Last updated: **2026-09-23** (through Project 1 Step 3; sections 11–12 added).

---

## 📑 Contents

| # | Topic | The interview question it answers |
|---|-------|-----------------------------------|
| 1 | [Stack vs Heap](#1-stack-vs-heap) | "What's the difference between stack and heap memory?" |
| 2 | [Pointers vs References](#2-pointers-vs-references) | "Pointer or reference — when do you use which?" |
| 3 | [const correctness](#3-const-correctness) | "How do you pass a large object to a function?" |
| 4 | [Classes, ctor & dtor](#4-classes-constructor--destructor) | "When does a destructor run?" |
| 5 | [RAII ⭐](#5-raii--the-most-important-idea-in-c) | "How does C++ manage memory without a garbage collector?" |
| 6 | [Smart pointers](#6-smart-pointers) | "unique_ptr vs shared_ptr?" |
| 7 | [Move semantics](#7-move-semantics) | "What does std::move do?" |
| 8 | [STL adapters](#8-stl-adapters-stack--queue--priority_queue) | "stack vs queue vs priority_queue?" |
| 9 | [Templates](#9-templates) | "What are templates and why does C++ have them?" |
| 10 | [Signed vs unsigned](#10-signed-vs-unsigned-the-size-trap) | "What does `.size()` return — and why is that a trap?" |
| 11 | [Inheritance & virtual 🟡](#11-inheritance--virtual-functions--introduced-not-yet-practised) | "What is polymorphism? Why a virtual destructor?" |
| 12 | [Header / source split](#12-splitting-code-into-h-and-cpp-files) | "Why separate `.h` and `.cpp` files?" |
| — | [Rapid-fire](#-rapid-fire-round) | 60-second recall drill |
| — | [Vocabulary](#-vocabulary-for-speaking) | Words to use so I sound senior |

---

## 1. Stack vs Heap

> ### 🎯 CUE — answer these out loud before reading on
> 1. Stack vs heap — five differences (who manages, speed, size, lifetime, what it holds)?
> 2. What are the **three** reasons to use the heap?
> 3. Draw the picture: `int* p = new int(100);` — where does `p` live, where does `100` live?
> 4. Define *memory leak* and *dangling pointer*.
> 5. Why does the address change every run?

### The one-table summary
| | **Stack** 📚 | **Heap** 🗄️ |
|---|---|---|
| Managed by | Compiler (automatic) | Me (manual `new`/`delete`) |
| Speed | Fast (just move a pointer) | Slower (must search for free space) |
| Size | Small (~1–8 MB) | Large (limited by RAM) |
| Lifetime | Dies when the function returns | Lives until `delete` |
| Holds | Local variables, function frames | Anything created with `new` |

### 🎤 SAY THIS
> "The stack is automatic memory — local variables live there, and they're destroyed automatically when the function returns. It's fast because allocation is just moving a pointer, but it's small, only a few megabytes. The heap is memory I request at runtime with `new`. It's slower and I'm responsible for freeing it, but it's large and it survives the function that created it. My default is the stack — I only reach for the heap when I need one of three things."

**Q: When do you need the heap?** — Three reasons, and only these three:
1. **The data must outlive the function.** Stack variables die on return.
2. **The size is only known at runtime.** Stack sizes are fixed at compile time.
3. **The data is too big for the stack.** A huge array would cause a stack overflow.

> "That's exactly what `vector` does internally — it stores its elements on the heap so it can grow at runtime."

### ★★ The key mental picture: the pointer and its target live in DIFFERENT places
```cpp
void f() { int* p = new int(100); }
```
```
   STACK              HEAP
 ┌───────┐         ┌───────┐
 │   p   │ ──────▶ │  100  │
 └───────┘         └───────┘
 the pointer        the value
```
When `f()` returns, `p` is destroyed — but the `100` is **not**. Nothing points to it now, so it can never be freed. **That is a memory leak.**

### ⚠️ Two bugs I must be able to name instantly
- **Memory leak** = heap memory that's never `delete`d. It's wasted for the program's entire life.
- **Dangling pointer** = a pointer to memory that has already died (e.g. returning the address of a local variable).

### ⚠️ Why the address changes every run — ASLR
**Address Space Layout Randomization.** The OS loads the program at a random location each run so attackers can't predict addresses (it defeats buffer-overflow exploits). So the absolute address *value* is meaningless — only the *relationships* matter (stack addresses cluster together; the heap is far away).

---

## 2. Pointers vs References

> ### 🎯 CUE
> 1. Five rows of the pointer-vs-reference table?
> 2. `int a=5; int& r=a; int b=10; r=b;` — what is `a` now, and why?
> 3. Why did every DSA function take `vector<int>&`?
> 4. `for (int x : v) x++;` — does this modify `v`? Why not?

```cpp
int x = 10;
int* p = &x;   // POINTER   — holds x's address. Access with *p
int& r = x;    // REFERENCE — an alias for x. Access directly as r
```

### The comparison table (memorise this)
| | Pointer `int* p` | Reference `int& r` |
|---|---|---|
| What it is | Holds an **address** | An **alias** (another name) |
| Access the value | Needs `*` (dereference) | Used **directly** |
| Can be null? | Yes (`nullptr`) | **No** — always refers to something |
| Can be re-pointed? | Yes | **No** — bound for life |
| Must initialise at declaration? | No | **Yes** |

### 🎤 SAY THIS
> "A reference is an alias — another name for an existing variable. A pointer is a variable that stores an address. The three practical differences are: a reference can't be null, it can't be re-seated to refer to something else, and it's used directly without dereferencing. So I prefer references when the thing definitely exists and won't change, and pointers when I need optional — meaning it might be null — or when I need to re-point it."

### ⚠️ THE trap: assigning to a reference does NOT re-seat it
```cpp
int a = 5;  int& r = a;  int b = 10;
r = b;      // does NOT make r refer to b — it copies b's VALUE into a
// result: a == 10, r == 10, b == 10
```
**Rule: assignment through a reference always writes to the value of the variable it aliases.** You can never change *what* it aliases.

### ⚠️ References don't cascade (a bug I actually hit)
```cpp
void addOne(vector<int>& v) {   // v is a reference to the caller's vector
    for (int x : v) x++;        // ❌ x is a COPY of each element — original unchanged
    for (int& x : v) x++;       // ✅ x is a reference to each element
}
```
`vector<int>&` and `int& x` are **two separate levels**. Having a reference to the container does not automatically give you references to its elements.

---

## 3. const Correctness

> ### 🎯 CUE
> 1. Three parameter-passing situations → what do you pass in each?
> 2. Why `const T&` rather than just `T&`?
> 3. What does `const` buy you *beyond* speed?

### 🎤 SAY THIS — the answer to "how do you pass a large object?"
> "For anything non-trivial that I only need to read, I pass by `const` reference — `const vector<int>&`. The reference avoids the copy, and the `const` guarantees I won't accidentally modify the caller's data. That's my default. I'd pass by value only for small types like `int` or `bool`, where a copy is cheaper than the indirection, and by non-const reference only when I genuinely need to modify the caller's object."

### The decision rule
| Situation | Pass as | Why |
|---|---|---|
| Small value (`int`, `char`, `bool`) | by value — `int x` | copy is cheap, simplest |
| Big object, I need to **modify** it | reference — `vector<int>& v` | no copy + changes original |
| Big object, I only **read** it | **const ref — `const vector<int>& v`** | no copy + protected ⭐ |

```cpp
void print(const vector<int>& v) {
    for (int x : v) cout << x;   // ✅ reading is fine, and no copy was made
    // v.push_back(5);           // ❌ compile error — v is const
}
```

### Why const matters beyond speed
> "`const` turns a potential runtime bug into a compile-time error. If a function promises not to modify its input, the compiler enforces that promise for me."

### ⚠️ Pass-by-value modifies the copy, not the original
```cpp
void f(vector<int> data) { data.push_back(99); }  // changes ITS OWN COPY only
```
The caller's vector is untouched — the copy is thrown away on return.

### Also exists (know they exist, deeper later)
- `const int* p` = can't change the **value**; `int* const p` = can't **re-point**. Read right to left.
- `int size() const` = a **const member function**; promises not to modify the object.

---

## 4. Classes, Constructor & Destructor

> ### 🎯 CUE
> 1. Constructor and destructor — syntax rules for each (name, return type, params)?
> 2. **When exactly does a destructor run?** (two cases + the guarantee)
> 3. Why is that guarantee the foundation of RAII?

```cpp
class Dog {
public:                                  // accessible outside (vs private:)
    string name;                         // member variable
    Dog(string n) { name = n; }          // CONSTRUCTOR — runs on creation
    ~Dog() { cout << "destroyed\n"; }    // DESTRUCTOR  — runs on destruction
    void bark() { cout << name << " woof\n"; }
};
```
- **Constructor:** same name as the class, no return type. Runs automatically when the object is created. Its job is **setup**.
- **Destructor:** `~` + class name, no parameters, no return type. **I never call it — C++ does.** Its job is **cleanup**.

### ★★ THE key fact (this is the whole foundation of RAII)
> **A stack object's destructor runs automatically when it leaves scope — at the closing `}` — and it is guaranteed, even if an exception is thrown.**

```cpp
{
    Dog d("Rex");
}   // ← d's destructor runs HERE. Guaranteed. Always.
```

**Q: When does a destructor run?** → "When the object goes out of scope, for a stack object. When `delete` is called, for a heap object. And critically, it's guaranteed to run even if an exception unwinds the stack — that guarantee is what makes RAII work."

---

## 5. RAII — the most important idea in C++

> ### 🎯 CUE — the highest-value box in this file
> 1. What does **RAII** stand for? (say the four words)
> 2. Explain it in one sentence.
> 3. What are the **two** ways manual `new`/`delete` fails, and how does RAII survive both?
> 4. Name five RAII types in the standard library.
> 5. "How does C++ manage memory without garbage collection?" — what's the keyword to drop?

### 🎤 SAY THIS (the full-marks answer)
> "RAII stands for **Resource Acquisition Is Initialization**. The idea is to tie a resource's lifetime to an object's lifetime: you acquire the resource in the constructor and release it in the destructor. Because C++ guarantees the destructor runs when the object goes out of scope — even if an exception is thrown — cleanup becomes automatic and impossible to forget. It's how C++ manages memory safely without a garbage collector. It's not just for memory either: file handles, mutex locks and sockets all use the same pattern."

### The shortest possible version (if they want one line)
> "Constructor takes the resource, destructor gives it back. Scope controls the lifetime."

### The code that shows it
```cpp
class IntBox {
public:
    int* data;
    IntBox(int v) { data = new int(v); }   // ACQUIRE in the constructor
    ~IntBox()     { delete data; }         // RELEASE in the destructor
};

void f() {
    IntBox box(42);
    // ... use box ...
}   // ← destructor runs here. delete happens automatically. Leak impossible.
```
I write `delete` **once**, inside the destructor. After that, cleanup is automatic forever.

### ⚠️ Why this beats manual new/delete
Manually matching `new` and `delete` fails in two ways: you forget, or an exception is thrown between them and skips the `delete` entirely. RAII survives both, because destructors run during **stack unwinding**.

### 🎤 The follow-up they always ask: "give me examples of RAII in the standard library"
> "`vector`, `string`, `unique_ptr`, `shared_ptr`, `fstream`, and `lock_guard` for mutexes. Every one of them acquires in its constructor and releases in its destructor — that's why I never have to `delete` a vector."

### 🎤 And: "how does C++ manage memory without garbage collection?"
> "Through RAII and deterministic destruction. In a garbage-collected language, cleanup happens at some unpredictable later time. In C++, the destructor runs at a precise, known moment — the closing brace. That's actually an advantage: it's deterministic, there are no GC pauses, and it works for any resource, not just memory."

**Keyword to drop: _deterministic destruction_.** It signals you understand the trade-off, not just the mechanism.

---

## 6. Smart Pointers

`#include <memory>` — RAII applied to pointers, pre-built by the standard library.

> ### 🎯 CUE
> 1. `unique_ptr` vs `shared_ptr` — when each?
> 2. **Why** can't a `unique_ptr` be copied? What breaks if it could?
> 3. How *do* you transfer a `unique_ptr`?
> 4. What does `shared_ptr` cost you?

### 🎤 SAY THIS
> "In modern C++ I don't write raw `new` and `delete`. I use `unique_ptr` by default — it represents a single owner, it can't be copied, so a double-delete is impossible, and it has zero runtime overhead compared to a raw pointer. I use `shared_ptr` only when ownership is genuinely shared — it reference-counts, so the object is freed when the last owner goes away, but that counting has a cost. And if I'm only borrowing something without owning it, I use a raw pointer or a reference."

### unique_ptr — the default
```cpp
unique_ptr<int> p = make_unique<int>(42);   // make_unique replaces raw `new`
cout << *p;                                  // dereference normally → 42
// auto-deletes when p leaves scope. No delete. Leak-proof, exception-safe.

unique_ptr<int> b = p;              // ❌ COMPILE ERROR — cannot be copied
unique_ptr<int> b = std::move(p);   // ✅ ownership TRANSFERS; p becomes nullptr
```
**Why copying is forbidden:** two `unique_ptr`s owning the same memory would both `delete` it → double-delete → crash. The compiler prevents it.

### shared_ptr — genuinely shared ownership
```cpp
shared_ptr<int> a = make_shared<int>(42);
shared_ptr<int> b = a;      // ✅ fine — now 2 owners, same int
cout << a.use_count();      // 2
```
Keeps a **reference count**: +1 per copy, −1 per destruction, freed at 0.
Analogy: a shared Google Doc — it exists while anyone has it open, and is deleted when everyone closes it.

### Decision table
| Need | Use |
|---|---|
| One owner (the common case) | **`unique_ptr`** — default, zero overhead |
| Genuinely shared ownership | `shared_ptr` — ref-count cost |
| Just borrowing, not owning | raw pointer or reference |

---

## 7. Move Semantics

> ### 🎯 CUE
> 1. Copy vs move — what happens to the source in each?
> 2. What does `std::move` **actually do** at runtime? (trick question)
> 3. lvalue vs rvalue — and why are rvalues safe to steal from?

### 🎤 SAY THIS
> "Move semantics let you transfer a resource instead of copying it. A copy duplicates everything and leaves the source intact — expensive for large data. A move steals the internals: the destination takes over the source's pointer to its heap buffer, and the source is left empty but valid. So a move is a few pointer assignments regardless of how much data there is. `std::move` doesn't actually move anything — it's a cast that marks a value as safe to steal from."

### Copy vs Move
- **Copy** = duplicate everything. Source keeps its data. **Expensive.**
- **Move** = steal the internals. Source is left empty but valid. **Cheap** (pointer swaps).
- Analogy: copy = photocopying 500 pages. Move = handing over the document.

```cpp
vector<int> a = {1,2,3};
vector<int> b = std::move(a);   // b takes a's buffer; a is now empty (valid, but unspecified)
```

### ★ The unique_ptr connection
```cpp
unique_ptr<int> a = make_unique<int>(42);
unique_ptr<int> b = std::move(a);   // ✅ ownership transfers: a → nullptr, b owns the 42
```
Copying a `unique_ptr` is forbidden (two owners = double-delete), but **moving** is allowed — ownership hands over and there's still exactly one owner. **This is how you transfer a `unique_ptr` — not by switching to `shared_ptr`.**

### lvalue vs rvalue
- **lvalue** = has a name, can be used again (`a`, `x`).
- **rvalue** = a temporary, disposable (`5`, `a + b`, a function's return value).
- rvalues are safe to steal from because nobody will use them again. `std::move` casts an lvalue so it can be treated like an rvalue.

---

## 8. STL Adapters: stack / queue / priority_queue

> ### 🎯 CUE
> 1. All three: ordering, and the method names for add / peek / remove?
> 2. One use case each.
> 3. `priority_queue` complexity for push, pop, top? How do you make it a **min**-heap?
> 4. Does `pop()` return the value?

| Adapter | Order | Add | Peek | Remove | Use for |
|---|---|---|---|---|---|
| `stack` | **LIFO** (last in, first out) | `push` | `top` | `pop` | brackets, DFS, undo |
| `queue` | **FIFO** (first in, first out) | `push` | `front` | `pop` | BFS |
| `priority_queue` | **largest first** (max-heap) | `push` | `top` | `pop` | top-K, scheduling, Dijkstra |

### 🎤 SAY THIS
> "All three are container adapters — they wrap an underlying container and expose a restricted interface. A stack is LIFO; I reach for it when the most recent item is the one I need next, like matching brackets or a depth-first search. A queue is FIFO — first in, first out — which is what breadth-first search needs. A priority_queue is a binary heap that always keeps the largest element on top, so push and pop are O(log n) while reading the top is O(1); I use it for top-K problems and Dijkstra."

```cpp
stack<char> s;  s.push('a'); s.push('b');  s.top();   // 'b' — the LAST one in
queue<char> q;  q.push('a'); q.push('b');  q.front(); // 'a' — the FIRST one in
priority_queue<int> pq; pq.push(3); pq.push(9); pq.push(1);  pq.top();  // 9 — always the max
```
Min-heap version: `priority_queue<int, vector<int>, greater<int>> pq;` → smallest on top.

### ⚠️ `pop()` removes but does NOT return the value
Two calls are needed — read, then remove:
```cpp
int x = s.top();  s.pop();   // the correct way to "pop and use"
```

---

## 9. Templates

> ### 🎯 CUE
> 1. What problem do templates solve? Why can't C++ just do what JavaScript does?
> 2. When the compiler sees `maxOf(3,7)` and `maxOf(2.5,1.5)` — what does it produce?
> 3. Is a template slower at runtime than a hand-written function? What's the phrase for this?
> 4. `printAll(vector<T>&)` vs `pushThree(T&)` — what does `T` become in each, and why the difference?
> 5. If you pass something without the required method, **when** does it fail — and why is that good?

### The problem
```cpp
int    maxOf(int a, int b)       { return (a > b) ? a : b; }
double maxOf(double a, double b) { return (a > b) ? a : b; }
string maxOf(string a, string b) { return (a > b) ? a : b; }
```
Only **three words** differ — the return type and two parameter types. The body is character-for-character identical. The logic is written once conceptually but typed three times.

**Q: Why can't C++ just be untyped like JavaScript?**
> "JavaScript checks types at runtime — it inspects the value while the program runs. C++ has no runtime type-checker; it has to emit machine code before the program ever runs, and comparing two ints compiles to different CPU instructions than comparing two doubles. So C++ needs the type at compile time — not to be strict, but because it physically can't generate the instructions without it."

### The solution
```cpp
template <typename T>
T maxOf(T a, T b) { return (a > b) ? a : b; }

maxOf(3, 7);       // compiler deduces T = int
maxOf(2.5, 1.5);   // compiler deduces T = double
```
`T` is a **placeholder for a type** — not a value, a *type*.

### 🎤 SAY THIS
> "A template is a recipe the compiler uses to generate functions — it's not a function itself. When I call `maxOf` with ints, the compiler **instantiates** a real `int maxOf(int,int)` and puts it in the binary. Call it with three different types and I get three actual functions compiled — exactly the three I'd have written by hand, I just didn't type them. That's why there's no runtime cost: all the genericity is resolved at compile time. It's a **zero-cost abstraction**."

**Keyword: _instantiation_.** The compiler generating a concrete function from the template.
**Keyword: _zero-cost abstraction_.** Generic in source, fully concrete in the binary.

### ★★ Where does `T` go? — the thing that trips people
Whatever part of the type you **write out literally**, `T` doesn't have to cover.

| Parameter | Passed `vector<int>` | `T` deduced as | Use when |
|---|---|---|---|
| `T value` | | `vector<int>` (the whole thing) | you want the **container** |
| `vector<T> value` | | `int` (the element) | you want the **element** |

```
your parameter:   vector<T>
what you passed:  vector<int>
                  vector matches vector ✓  →  T = int
```

⚠️ **My actual bug:** I wrote `printAll(T value)`, so `T` swallowed the whole `vector<int>` and the body tried `cout << (entire vector)`. Fix: `printAll(const vector<T>& value)`.

### The two flavours side by side
```cpp
template <typename T>
void printAll(const vector<T>& v) {     // T = the ELEMENT type
    for (const T& x : v) cout << x << " ";
    cout << endl;
}

template <typename T>
void pushThree(T& c) {                  // T = the WHOLE CONTAINER
    c.push(1); c.push(2); c.push(3);
}
stack<int> s; queue<int> q; priority_queue<int> pq;
pushThree(s); pushThree(q); pushThree(pq);   // all three work
```
Which is right depends on **what the body does**: `printAll` loops over elements; `pushThree` calls a method on the container itself.

### 🎤 Compile-time duck typing (a strong thing to say)
> "`pushThree` never declares 'this must be a stack'. It says: any type that has a `.push()` taking an int. `stack`, `queue`, `priority_queue`, `vector` all satisfy that. It's duck typing, but resolved at **compile time** — if the type doesn't have `.push()`, the build fails on my machine rather than throwing in production. That's the same philosophy as `const`: turn a possible runtime bug into a guaranteed compile-time error."

### ⚠️ Reading template error messages
They're 200 lines long. **The answer is always in the first two.**
```
In instantiation of 'void printAll(T) [with T = std::vector<int>]':     ← what T was deduced as
error: no match for 'operator<<' ... 'std::ostream' and 'std::vector<int>'   ← what went wrong
```
Everything after that is the compiler listing every overload it *does* know. Ignore it.

### ⚠️ Other gotchas
- `template <typename T>` applies to **one** function — the one directly below it. Two functions = write it twice.
- In a range-for inside a template, use `const T&` not `T` — `T` could be a huge type, and you don't know what it'll be.
- `typename` and `class` are interchangeable here: `template <class T>` means the same thing.
- **The whole STL is templates.** `vector<int>`, `map<string,int>`, `stack<char>` — the `<>` *is* a template argument.

---

## 10. Signed vs Unsigned (the `.size()` trap)

> ### 🎯 CUE
> 1. What type does `.size()` return, and why does that matter?
> 2. `int n = -3; if (n > text.size())` — what does this evaluate to, and why?
> 3. What flag makes the compiler warn you about it?

### The trap
Every STL container's `.size()` returns **`size_t`** — an **unsigned** type. It has no negatives.
Compare a signed `int` against it and C++ silently converts your `int` to unsigned:

```cpp
string text = "Hello";     // size() == 5
int n = -3;
if (n > text.size()) ...   // ⚠️ TRUE! -3 became 18446744073709551613
```
`-3` doesn't convert to unsigned — its **bit pattern is reinterpreted**, wrapping to the top of
the range. So a negative number compares as *enormous*, and the guard you wrote does the opposite
of what you intended.

### 🎤 SAY THIS
> "`.size()` returns `size_t`, which is unsigned. If I compare it against a signed `int`, the int
> gets converted to unsigned, and a negative value wraps around to a huge positive one — so a guard
> like `if (n > size())` passes when it shouldn't. I either cast explicitly, or guard against
> negatives first. And I build with `-Wall` so the compiler tells me: it's the `-Wsign-compare`
> warning."

### The fix
```cpp
void remove(int n) {
    if (n <= 0) return;                          // reject negatives explicitly
    if (n > (int)text.size()) n = text.size();   // cast → both sides signed
    text.erase(text.size() - n);
}
```

### ⚠️ It crashed for real in my DeleteCommand (2026-09-19)
```cpp
deletedText = b.getText().substr(b.getText().size() - count);   // buffer "Hi", count 10
```
`2 - 10` on `size_t` → 18446744073709551608 → `substr` threw **`std::out_of_range`** and the
program terminated. The error message even printed the giant number. **Fix: clamp first, subtract after.**
```cpp
if (count > b.size()) count = b.size();   // b.size() returns int, so no cast needed
```
Rule: **before subtracting from a `.size()`, prove the result can't go negative.**

### ⚠️ Same family as my LeetCode `char` bug
`unordered_map<char,int>` with numeric keys — `char` is −128..127, so `6142` overflowed and the
answer was silently wrong. **Same root cause: the type couldn't hold the value, so it became
something else without telling me.** Always ask: *can this type hold every value I'll put in it?*

### 🎤 Always build with warnings on
> "I compile with `-Wall`, and on a team I'd push for `-Werror` so warnings fail the build. Most
> warnings are real bugs the compiler found for free."
```
g++ -Wall file.cpp -o file      # all warnings
g++ -Wall -Wextra file.cpp      # even more
```

### ⭐ Design lesson from the same exercise: clamping
When someone asks a container for more than it has (`remove(100)` on 2 chars), **never crash**.
Choose deliberately: clamp to what exists, or refuse. Clamping is usually better — it produces
fewer downstream cases to handle. (Same decision as `if (st.empty()) return false;` in Valid
Parentheses.) Interviewers ask "what if the input is invalid?" specifically to see if you thought
about it. *"It would crash"* is a failing answer.

---

## 11. Inheritance & Virtual Functions 🟡 *introduced, not yet practised*

> 🟡 **Status (2026-09-23):** I was *given* this code in Project 1. I haven't built it myself
> from a blank file yet. A standalone mini-lesson comes next. Don't mark this confident until I have.

> ### 🎯 CUE
> 1. Why can't `stack<InsertCommand>` hold the whole undo history?
> 2. What do `virtual`, `= 0` and `override` each do?
> 3. Why must a base class have a **virtual destructor**?
> 4. What is **slicing**, and why do pointers fix it?
> 5. Templates vs virtual: when is each one resolved, and what does it cost?

### The problem it solved in my editor
My undo history contains **both** `InsertCommand`s and `DeleteCommand`s, mixed in whatever order the
user worked. A `stack<T>` holds one type only. `stack<InsertCommand>` can't take deletes, and vice versa.

### The solution: a shared parent type
```cpp
class Command {                              // the base class
public:
    virtual void execute(Buffer& b) = 0;     // pure virtual: no body, every child MUST provide one
    virtual void undo(Buffer& b) = 0;
    virtual ~Command() {}                    // virtual destructor (see below)
};

class InsertCommand : public Command {       // "InsertCommand IS A Command"
    std::string text;
public:
    void execute(Buffer& b) override;        // override: "I'm replacing a virtual function"
    void undo(Buffer& b) override;
};
```
- **`virtual`**: which function runs is decided at **runtime**, by the object's real type.
- **`= 0`**: *pure virtual*. A class with one is **abstract**, so you can't create a plain `Command`.
- **`override`**: asks the compiler to check. If my signature doesn't match the parent's (say I
  forget a `&`), it's a compile error instead of a silent brand-new function that never gets called.
- **Virtual destructor**: when a child is deleted through a base pointer, only a virtual destructor
  makes sure the child's part is destroyed too. **Rule: any class meant to be inherited from gets one.**

### Why the stack holds `unique_ptr<Command>` and not `Command`
- **Slicing:** a `stack<Command>` slot is `Command`-sized. Copying an `InsertCommand` into it chops off
  the extra parts (its `text`), and virtual dispatch stops working.
- **A pointer** is the same size whatever it points to, so the object stays whole on the heap.
- **`unique_ptr`** instead of `Command*`: the commands get deleted automatically (RAII), so there's no leak.
> **Pointer because of slicing. `unique_ptr` because of cleanup.**

### 🎤 SAY THIS (practise once it's mine)
> "Polymorphism lets me treat different types through one common interface. I give them a base class
> with virtual functions, and when I call a virtual function through a base pointer or reference,
> the version for the object's real type runs, decided at runtime. It has to go through a pointer or
> reference, because storing a derived object by value in a base-type slot slices off the derived part.
> In my undo system, the undo stack holds `unique_ptr<Command>`, so inserts and deletes live in one
> stack, and `undo()` does the right thing for each without any if-statements. Base classes get a
> virtual destructor, and I mark overrides with `override` so the compiler checks the signatures."

### Templates vs virtual (the comparison interviewers like)
| | Templates | Virtual functions |
|---|---|---|
| Type decided | **compile time** | **runtime** |
| Cost | zero (a separate function per type) | one indirect call through the vtable |
| Use when | the types are known when compiling | the types are only known while running (a mixed collection) |

---

## 12. Splitting Code into `.h` and `.cpp` Files

> ### 🎯 CUE
> 1. What goes in the header, and what goes in the `.cpp`?
> 2. What does `#pragma once` prevent?
> 3. Why no `using namespace std;` in a header?
> 4. What command builds a multi-file project with `include/` and `src/` folders?

### The rule: the header says *what exists*, the `.cpp` says *how it works*
```cpp
// include/Buffer.h: declarations only
#pragma once                       // don't include this file twice
#include <string>
class Buffer {
    std::string text;              // std:: spelled out, never `using namespace std;` in a header
public:
    void insert(const std::string& s);
};

// src/Buffer.cpp: definitions, each prefixed with the class name
#include "Buffer.h"
void Buffer::insert(const std::string& s) { text += s; }
```
- **`Buffer::`** says "this function belongs to the class `Buffer`".
- **No `using namespace std;` in headers**, because every file that includes the header inherits it.
- **Build:** `g++ -Wall -Iinclude src/*.cpp -o editor`. `-Iinclude` tells the compiler where the
  headers are; `src/*.cpp` compiles every source file together.

### 🎤 SAY THIS
> "Headers hold declarations, the interface other code compiles against, and `.cpp` files hold the
> implementations. That way each `.cpp` compiles on its own, and changing an implementation doesn't
> force every file that uses the class to recompile. I use `#pragma once` to stop double inclusion,
> and I never put `using namespace std` in a header, because it leaks into every file that includes it."

### ⚠️ What actually bit me
When I copied my working code into the new files, the **old unfixed `execute`** came along with it.
The build was clean, and only running the tests showed the wrong output (`[HeHello]`).
**A clean build doesn't mean a correct program. Re-run the tests after every move or copy.**

---

## ⚡ Rapid-fire round
*Cover the right column. Answer out loud. Under 10 seconds each.*

| Question | Answer |
|---|---|
| RAII stands for? | **R**esource **A**cquisition **I**s **I**nitialization |
| RAII in one line? | Acquire in the constructor, release in the destructor; scope controls lifetime |
| When does a destructor run? | At scope exit for stack objects; on `delete` for heap objects — guaranteed even on exception |
| Memory leak? | Heap memory that's never freed |
| Dangling pointer? | A pointer to memory that has already died |
| Three reasons to use the heap? | Outlive the function; runtime size; too big for the stack |
| Reference vs pointer — 3 differences? | Can't be null; can't be re-seated; used without `*` |
| How to pass a large read-only object? | `const T&` |
| Default smart pointer? | `unique_ptr` |
| Why can't `unique_ptr` be copied? | Two owners would both delete it → double-delete |
| How do you transfer a `unique_ptr`? | `std::move` |
| What does `std::move` actually do? | Nothing at runtime — it's a cast marking a value as safe to steal from |
| `shared_ptr` cost? | Reference counting overhead |
| stack / queue / priority_queue order? | LIFO / FIFO / largest-first |
| Does `pop()` return the value? | No — use `top()`/`front()` first |
| Why is C++ memory management better than GC? | Deterministic destruction — no unpredictable pauses, works for any resource |
| What is a template? | A recipe the compiler uses to **generate** functions — not a function itself |
| What's the word for the compiler generating one? | **Instantiation** |
| Are templates slower at runtime? | No — **zero-cost abstraction**, all resolved at compile time |
| Why does C++ need types when JS doesn't? | It emits machine code before running; different types = different CPU instructions |
| `T v` vs `vector<T> v` given a `vector<int>`? | `T`=`vector<int>` vs `T`=`int` — whatever you write literally, `T` needn't cover |
| Template error message — where's the answer? | The **first two lines**. Ignore the other 200. |
| Missing method on a template arg fails when? | **Compile time** — the build fails instead of production |
| What does `.size()` return? | `size_t` — **unsigned**. Comparing to a signed int is a trap |
| `int n=-3; n > text.size()`? | **true** — −3 wraps to ~1.8e19 when converted to unsigned |
| Flag to catch that? | `-Wall` (the `-Wsign-compare` warning); `-Werror` to make it fatal |
| Asked to remove more than exists? | **Clamp** — never crash. Fewer downstream cases than refusing |
| `substr(size - count)` with count > size? | Unsigned wrap → `std::out_of_range`. **Clamp before subtracting** |
| What does `virtual` do? | Picks the function by the object's **real** type, at runtime |
| `= 0` on a virtual function? | Pure virtual: no body, the class becomes **abstract** |
| Why `override`? | Compiler checks the signature really overrides; typos become errors |
| Why a virtual destructor? | So deleting a child through a base pointer destroys the child's part too |
| What is slicing? | Storing a derived object by value in a base slot chops off the derived part |
| Why `stack<unique_ptr<Command>>`? | Pointer → no slicing; `unique_ptr` → automatic cleanup |
| Templates vs virtual? | Compile time + zero cost vs runtime + a vtable call |
| `.h` vs `.cpp`? | Header = what exists (declarations); `.cpp` = how it works (definitions) |
| `#pragma once`? | Stops a header being included twice |
| `using namespace std;` in a header? | Never, it leaks into every file that includes it |

---

## 🔁 Revision schedule (spaced repetition, no app needed)

Spacing reviews across **days** beats repeating them in one sitting. Track it here — tick a box each pass.

| Topic | 1st (same day) | 2nd (+3 days) | 3rd (+1 week) | 4th (+3 weeks) | Confident? |
|---|---|---|---|---|---|
| 1. Stack vs heap | [ ] | [ ] | [ ] | [ ] | |
| 2. Pointers vs references | [ ] | [ ] | [ ] | [ ] | |
| 3. const correctness | [ ] | [ ] | [ ] | [ ] | |
| 4. Ctor / dtor | [ ] | [ ] | [ ] | [ ] | |
| 5. **RAII** ⭐ | [ ] | [ ] | [ ] | [ ] | |
| 6. Smart pointers | [ ] | [ ] | [ ] | [ ] | |
| 7. Move semantics | [ ] | [ ] | [ ] | [ ] | |
| 8. STL adapters | [ ] | [ ] | [ ] | [ ] | |
| 9. Templates | [ ] | [ ] | [ ] | [ ] | |
| 10. Signed vs unsigned | [ ] | [ ] | [ ] | [ ] | |
| 11. Inheritance & virtual 🟡 | [ ] | [ ] | [ ] | [ ] | (after the mini-lesson) |
| 12. `.h` / `.cpp` split | [ ] | [ ] | [ ] | [ ] | |

**A pass = cover the section, answer the 🎯 CUE box out loud, then check.** Two minutes per topic.
If you fail one, it goes back to the start of the schedule — don't tick it out of optimism.

---

## 🗣️ Vocabulary for speaking
Using the precise word signals depth. Weak phrasing → precise phrasing:

| Instead of… | Say… |
|---|---|
| "it deletes itself" | "the destructor runs at scope exit" |
| "it's automatic" | "**deterministic destruction**" |
| "it doesn't copy" | "it avoids a copy — I pass by **const reference**" |
| "it's fast" | "it's **O(1)**" / "it's a few pointer assignments" |
| "you can't copy it" | "copying is **deleted** — it enforces **single ownership**" |
| "it counts users" | "it's **reference-counted**" |
| "it takes the data" | "it **transfers ownership**" |
| "the memory is lost" | "that's a **leak** — the memory is unreachable and unfreeable" |
| "for any type" | "it's **generic** — the compiler **instantiates** a version per type" |

### Sentence starters for interviews
- "The trade-off here is…"
- "My default would be X, and I'd only reach for Y when…"
- "The guarantee the language gives me is…"
- "In terms of complexity, that's O(…) time and O(…) space, because…"

---

## 📅 Session log
| Date | Added |
|---|---|
| 2026-09-10 | File created — Lessons 1–8 consolidated, RAII written up properly, speaking blocks + rapid-fire added |
| 2026-09-10 | Structure upgraded after checking the retention research: 🎯 CUE boxes per section (Cornell cue-column — forces retrieval before reading), the "never revise by reading" rule, and a spaced revision schedule |
| 2026-09-10 | **Lesson 8: Templates** written up — instantiation, zero-cost abstraction, `T` placement (`vector<T>` vs `T`), compile-time duck typing, reading template errors. Exercise: `cpp/exercises/08-templates.cpp` |
| 2026-09-12 | **Project 1 started** (text editor). Lesson 10 added: signed/unsigned `.size()` trap, `-Wall`, and clamping as a design decision — all from building `Buffer` |
| 2026-09-23 | Caught up on 09-12 → 09-23: section 10 + the real DeleteCommand `out_of_range` crash; **section 11 Inheritance & virtual** (🟡 given, not yet practised); **section 12 `.h`/`.cpp` split** (+ the copy-reintroduced-bug lesson); 12 rapid-fire rows |
