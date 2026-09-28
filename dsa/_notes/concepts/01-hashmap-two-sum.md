# DSA Theory · Lesson 2 — HashMap (+ Two Sum)

## What a HashMap IS
Stores **key → value** pairs. Superpower: check "does this key exist?" and "get its value"
in **O(1)** — instant, NO scanning. (Array lookup = O(n) scan; HashMap = O(1).)
Analogy: coat-check counter — show ticket (key), get coat (value) instantly, no searching.

### JS Map API (memorize)
```js
const map = new Map();
map.set(key, value); // store
map.get(key);        // value, or undefined if missing
map.has(key);        // true/false — exists?   ← O(1) magic
map.delete(key);     // remove
```

## When to reach for a HashMap (the pattern)
**"My brute force is slow because it keeps SEARCHING for something."**
→ Replace the O(n) search/scan with an O(1) HashMap lookup.
This single pattern solves a huge fraction of array/string problems.

---

## Problem: Two Sum (LeetCode #1, Adobe-tagged)
Return INDICES of the two numbers that add to target. Exactly one solution; no reuse of an element.

### Brute force — Time O(n²), Space O(1)
```js
function twoSum(nums, target) {
  const len = nums.length;
  for (let i = 0; i < len; i++) {
    for (let j = i + 1; j < len; j++) {     // j = i+1 → no self-pair, no dup pairs
      if (nums[i] + nums[j] === target) return [i, j];
    }
  }
}
```

### Optimal (HashMap) — Time O(n), Space O(n)
**Key idea:** for number x, partner = `target - x`. Walk once; CHECK before you STORE.
```js
function twoSumOptimal(nums, target) {
  const seen = new Map();                 // number → its index
  for (let i = 0; i < nums.length; i++) {
    const need = target - nums[i];
    if (seen.has(need)) return [seen.get(need), i];  // CHECK first
    seen.set(nums[i], i);                             // then STORE
  }
}
```
**Why check-before-store:** ensures we pair with an EARLIER element, never the number itself.
**Dry run [3,2,4] t=6:** on 3 need 3 (no) store{3:0} → on 2 need 4 (no) store{2:1} → on 4 need 2 (YES@1) → [1,2].

## Why a HashMap and not an array? (the real insight)
- Both are O(n) SPACE — that's not the reason.
- HashMap `has/get` = **O(1)**. Array `includes/indexOf` = **O(n) scan**.
- An array lookup inside the loop → back to O(n²). The HashMap's O(1) lookup is the WHOLE point.

## Trade-off named (say this in interviews)
"I traded O(n) extra space for time, cutting O(n²) → O(n). The HashMap gives O(1) lookups,
so I only need a single pass."
