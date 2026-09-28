# C++ Mastery · Lesson 4 — Classes, Constructor & Destructor

## Class = data + methods bundled into one type
```cpp
class Dog {
public:                 // accessible outside (vs private: only the class)
    string name;        // member variable (data)
    void bark() { cout << name << " woof\n"; }  // method
};
Dog d; d.name = "Rex"; d.bark();
```

## Constructor — auto SETUP when object is CREATED
Same name as class, no return type.
```cpp
Dog(string n) { name = n; }   // runs automatically at `Dog d("Rex");`
```

## Destructor — auto CLEANUP when object is DESTROYED
`~` + class name, no params, no return. You never call it — C++ does.
```cpp
~Dog() { cout << "destroyed\n"; }
```

## ★★ THE key fact (foundation of RAII) ★★
A stack object's destructor runs AUTOMATICALLY when it leaves scope (at the `}`),
GUARANTEED — even if an exception is thrown.
```
start / constructed / inside block / destroyed / end
```
`destroyed` prints at the inner block's `}`, BEFORE `end`. Cleanup is tied to scope.

→ So: put `delete`/cleanup INSIDE a destructor → cleanup becomes automatic & leak-proof.
   That is RAII (next lesson). Ctor acquires, dtor releases, scope controls lifetime.

## RAII — the payoff (write delete ONCE, cleanup is automatic forever)
Class OWNS a resource: acquire in ctor, release in dtor.
```cpp
class IntBox {
public:
    int* data;
    IntBox(int v) { data = new int(v); }  // acquire
    ~IntBox()     { delete data; }         // release (auto-runs at scope `}`)
};
// main just uses `box` — NEVER calls delete. Dtor frees it automatically. No leak possible.
```
**RAII = resource lifetime tied to object lifetime.** Dtor guaranteed at scope end (even on
exception) → automatic, leak-proof cleanup. vector / string / unique_ptr are all RAII —
that's why you never `delete` a vector.
