# P1 · Lesson 1b — Closures

## ⚠️ ++c vs c++ (missed this in a closure output question)
- `++c` PRE-increment → CHANGE then GIVE → returns the NEW value.
- `c++` POST-increment → GIVE then CHANGE → returns the OLD value.
Example: `let c=0; const f=()=>++c;` → f() returns 1,2,3...  (with `c++` it'd return 0,1,2...)
Shows up constantly in R1 output-prediction questions.

## Definition
**Closure = a function + the variables it remembers from where it was born.**
An inner function keeps its outer variables ALIVE even after the outer function has returned.
(It's just the scope chain + memory.)

## THE core rule (the one I got wrong first)
**Every time a function RUNS, it creates a brand-new scope = a fresh set of local variables.**
- Same code run twice → TWO independent variables (same name, different boxes).
- A closure captures the variables of a SPECIFIC invocation of the outer function.

So `const a = makeCounter(); const b = makeCounter();` → a and b have SEPARATE private `count`s.
→ `a() a() b() a()` prints `1 2 1 3` (NOT 1 2 3 4).

## Uses
- **Private state / encapsulation:** `count` is reachable only through the returned fn. No outside access.
- **Factory pattern:** call outer fn with different args to stamp out specialized fns that each
  remember their own config. `makeMultiplier(2)` → `double`; `makeMultiplier(3)` → `triple`. No interference.
- This is how debounce, throttle, and React hooks work internally.

## THE famous loop trap (Adobe WILL ask)
```js
for (var i = 0; i < 3; i++) {
  setTimeout(() => console.log(i), 100);
}
// prints 3 3 3
```
**Why:** `var` is function-scoped → ONE shared `i` for the whole loop. Callbacks run AFTER the
loop ends, when `i` has climbed to 3. All three see the same `i = 3`.

**Fix:** use `let` → block-scoped → a NEW `i` per iteration → each callback closes over its own.
```js
for (let i = 0; i < 3; i++) { setTimeout(() => console.log(i), 100); } // prints 0 1 2
```

### Interview-perfect answer (memorize)
"It prints 3 3 3. `var` is function-scoped, so all three callbacks close over the same single `i`,
which is 3 after the loop ends. Switching to `let` gives each iteration its own block-scoped `i`,
so it prints 0 1 2."

### The "box" mental model (this is what made it click)
A variable = a BOX in memory. The whole question: ONE box reused, or a NEW box each turn?
- **`var` = ONE shared box** (function-scoped). Loop scribbles 0,1,2,3 on the SAME whiteboard,
  then leaves. All callbacks read the same whiteboard LATER → all see 3. → `3 3 3`
- **`let` = a NEW box each turn** (block-scoped). Each callback gets its own sticky note frozen
  at 0,1,2. → `0 1 2`
- Callbacks capture the BOX, not the value. They don't read it until they run (after the loop).

### KEY: the trap needs BOTH ingredients
`var` + DELAYED execution (setTimeout / event handler / async). Remove either and no surprise:
- `var` + immediate `console.log(i)` inside loop → `0 1 2` (read before loop moves on)
- `let` + delay → `0 1 2` (own box each time)
- Only **`var` + delay** → `3 3 3`

## Verified I understand
- Single counter 1 2 3 ✓
- Multiplier factory independence (10 15 20) ✓
- Loop trap 3 3 3 + reasoned the why ✓
- MISSED first: two counters share state (they DON'T) — corrected ✓
