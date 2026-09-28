# P1 · Lesson 3 — Promises & async/await

## Why Promises exist
Slow work finishes LATER. Old way = callbacks → nesting → "callback hell" (unreadable, hard errors).
Promises flatten this and give clean error handling.

## What a Promise IS
An object for a value that ISN'T ready yet but WILL be (or will fail). Like a coffee-shop RECEIPT.
**3 states:** pending → (fulfilled with a value) OR (rejected with an error). Once settled, LOCKED.

## Creating one: new Promise + resolve
```js
const p = new Promise((resolve) => {
  // JS HANDS you `resolve` — it's a "DONE!" button function.
  // ...do work (can be slow/async)...
  resolve("3");   // PRESS it → Promise becomes fulfilled with "3"
});
```
- The function inside `new Promise(...)` runs **synchronously, immediately**.
- `resolve(X)` → X flows into `.then((X) => ...)`. THAT is the connection.
- Why `resolve` (not `return`)? So you can signal "done" LATER, e.g. inside a setTimeout —
  you can't `return` from a callback that already ended, but you CAN press `resolve` later.
- (There's also `reject(err)` → flows into `.catch((err)=>...)`.)

## Consuming: .then / .catch  (these callbacks are MICROTASKS)
```js
fetchData().then(result => ...).catch(error => ...);
```

## async/await — readable syntax on top of Promises (same thing underneath)
- `async` before a function → it works with Promises, always returns a Promise.
- `await p` → PAUSE here until p resolves, then give me the value. `const x = await p;`
- `const x = await p;` is the readable form of `p.then(x => ...)`.
- Errors: use normal `try/catch` instead of `.catch`.

## ★★ ORDERING RULES (interview gold) ★★
1. The `new Promise(executor)` body runs SYNC. `.then` runs ASYNC (microtask).
   ```js
   console.log("1");
   const p = new Promise(r => { console.log("2"); r("3"); }); // 2 is SYNC
   p.then(v => console.log(v));   // 3 is a microtask
   console.log("4");
   // → 1 2 4 3
   ```
2. In an async fn, everything BEFORE the first `await` runs SYNC. Code AFTER await resumes
   as a microtask. `await` pauses the FUNCTION but does NOT block the program.
   ```js
   console.log("A");
   async function run(){ console.log("B"); await Promise.resolve(); console.log("C"); }
   run();
   console.log("D");
   // → A B D C
   ```

## ★ "await pauses the FUNCTION, not the PROGRAM" (key conceptual clarity)
Waiting ≠ freezing. When `f` hits `await`, f steps aside and schedules its rest as a microtask;
the THREAD is free — other code (and the UI) keeps running. Restaurant: customer awaiting food
reads a book while the waiter serves other tables. Async avoids FREEZING, not WAITING.
- A BLOCKING wait freezes the whole thread (no clicks). `await` does NOT — only the dependent
  function pauses; everything else runs.

## ★★ TRAP: everything AFTER await waits — even lines that don't need the value
`await` pauses the function at that line, so ALL code below it waits, needed or not.
```js
const user = await fetchUser();   // 1s
const news = await fetchNews();   // +1s  → 2s total ❌ (news doesn't need user!)
```
**Fix — start independent work first, then await (runs in parallel):**
```js
const up = fetchUser(); const np = fetchNews();   // both START now
const user = await up; const news = await np;     // ~1s total ✅
// idiomatic:
const [user, news] = await Promise.all([fetchUser(), fetchNews()]);  // ~1s ✅
```
Principle: `await` only the things a line genuinely DEPENDS on. Independent async work →
kick it all off first / use Promise.all so it runs concurrently.
(Classic interview Q: "why is this async code slow?" → sequential awaits on independent tasks.)

## Promise combinators — all / allSettled / race (know WHEN to use which)
Take an ARRAY of promises that all START concurrently.

| Method                | Resolves when            | On a rejection                         |
|-----------------------|--------------------------|----------------------------------------|
| `Promise.all`         | ALL succeed              | REJECTS IMMEDIATELY (all-or-nothing)   |
| `Promise.allSettled`  | ALL settle (ok or fail)  | NEVER rejects — gives status of each   |
| `Promise.race`        | FIRST settles            | first to settle wins (success OR fail) |

- **all** → "need everything; abort if anything fails." Results array in INPUT order.
- **allSettled** → "try everything, tell me what worked." Always full array of
  `{status:'fulfilled', value}` | `{status:'rejected', reason}`.
- **race** → "first answer wins / timeout" (race request vs a reject-after-5s timer).

### ★ Promise.all all-or-nothing (interview trap)
```js
const results = await Promise.all([ Promise.resolve("A"), Promise.reject("B failed"), ... ]);
console.log(results);   // NEVER runs — the await LINE THROWS before `results` is assigned
```
One rejection → the whole `await` line throws → you get NOTHING (not partial, not error-in-array).
Wrap in try/catch → jumps to catch, which receives the rejection REASON ("B failed").
Want results despite failures? → use `allSettled`.

## Error handling with async/await = normal try/catch
```js
try { const data = await fetchData(); }   // if it REJECTS...
catch (error) { /* ...jumps here, error = rejection reason */ }
```
Cleaner than .catch — async errors handled like normal synchronous errors.

## Full async chain (the complete mental model)
callbacks → Promises (.then/.catch) → async/await → all scheduled via the Event Loop's
MICROTASK queue (which drains before macrotasks/setTimeout).
