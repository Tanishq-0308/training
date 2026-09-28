# P1 · Lesson 2 — The Event Loop

## The core problem it solves
JS has ONE thread (one worker) — does ONE thing at a time. So how does a 2-second `fetch`
not FREEZE the whole page? → The Event Loop. Slow work is offloaded; JS keeps moving.

## The players (restaurant analogy)
- **Call Stack** = the single waiter. Where code actually runs, one thing at a time.
- **Web APIs** = the kitchen. Browser handles slow stuff (setTimeout, fetch, DOM events) in the
  background on other threads. JS hands it off and moves on — does NOT wait.
- **Callback Queue + Event Loop** = pickup line + the rule. When a bg task finishes, its callback
  joins a queue. Event Loop's ONE job: when the Call Stack is EMPTY, move the next callback onto it.

## ★ setTimeout(fn, 0) does NOT mean "run now"
It means: run fn AFTER all current synchronous code finishes AND the stack is empty.
The 0 is a MINIMUM delay; the callback must still go through the queue.
→ This is WHY yesterday's loop trap callbacks ran "after the loop": the whole for-loop is sync
  and runs to completion first, THEN queued callbacks fire.

## ★★ TWO queues with different priority (the interview key) ★★
- **Macrotask queue:** setTimeout, setInterval, DOM events.
- **Microtask queue:** Promises (.then, async/await).
- **RULE: sync code → drain the ENTIRE microtask queue → THEN one macrotask → repeat.**
  Microtasks (Promises) ALWAYS beat macrotasks (setTimeout), even setTimeout(…,0).
  (Microtasks = VIP guests; served before any regular order.)

### Priority order to say in interview
**Synchronous → ALL microtasks (Promises) → then macrotasks (setTimeout).**

## Worked examples I got RIGHT
```js
console.log("1");
setTimeout(()=>console.log("2"),0);        // macrotask
Promise.resolve().then(()=>console.log("3"));// microtask
console.log("4");
// → 1 4 3 2   (sync 1,4; micro 3; macro 2)
```
Boss level:
```js
console.log("A");
setTimeout(()=>console.log("B"),0);
Promise.resolve().then(()=>{ console.log("C"); setTimeout(()=>console.log("D"),0); });
Promise.resolve().then(()=>console.log("E"));
console.log("F");
// → A F C E B D
```
- A,F sync. Micro queue [C,E] drains next. C schedules D as a NEW macrotask → joins BEHIND B.
- Macro queue [B,D] runs FIFO → B then D.
- Key: E (micro) beats B (macro); B beats D because D was queued later (FIFO within macro queue).

## Interview one-liner
"setTimeout is a macrotask, Promises are microtasks. The event loop drains the whole microtask
queue before any macrotask — so a Promise callback runs before a setTimeout(…,0) even if the
timeout was scheduled first."
