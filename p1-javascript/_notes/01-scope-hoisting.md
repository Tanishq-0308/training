# P1 · Lesson 1 — Scope & Hoisting

## Scope = what variables you can "see" from a place in code
- **Global** — outside any function. Visible everywhere.
- **Function** — `var`/`let`/`const` inside a function. Visible only inside it.
- **Block** — `let`/`const` are ALSO trapped in nearest `{ }`. `var` is NOT (ignores blocks, respects only functions).
- **Scope chain:** inner scope can look OUTWARD to find a variable. Outer scope can NEVER look inward. (One-way glass.)

## The two errors — know the difference (interview trap)
- **`undefined`** = the variable EXISTS but has no value yet. (a value)
- **`ReferenceError: x is not defined`** = the variable does NOT exist in this scope. (a failure)

## Hoisting — JS runs functions in 2 passes
1. **Setup pass:** scan & register declarations BEFORE running any line.
   - `var x` → hoisted AND initialized to `undefined`.
   - `let`/`const` → hoisted but NOT initialized → sit in the **Temporal Dead Zone (TDZ)**.
2. **Execution pass:** run lines top-to-bottom; ASSIGNMENTS happen at their line.

`var x = 1` is really TWO steps:
- `var x`  → hoisted to top (value `undefined`)
- `x = 1`  → stays put, runs in pass 2

## One-liners to say in an interview
- "It walks the **scope chain** outward."
- "`var` is hoisted and initialized to `undefined`; `let`/`const` are hoisted but in the **TDZ**."
- "That's `undefined` (the value) vs a `ReferenceError` (no such variable)."

## Verified I understand (got these right)
- Scope chain lookup (line A=10) ✓
- Block scope: `var` escapes `if`, `let` doesn't ✓
- Hoisting: `var` before decl = `undefined`, `let` before decl = ReferenceError (TDZ) ✓
