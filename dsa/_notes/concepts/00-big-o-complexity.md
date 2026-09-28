# DSA Theory · Lesson 1 — Time & Space Complexity (Big-O)

## The core question Big-O answers
"As the input size **n** gets bigger, how does the number of operations GROW?"
- We don't count exact ops (CPU-dependent noise). We care about the SHAPE of growth.
- Ask: if n doubles, what happens to the work?

## Complexity classes (slowest-growing → fastest)
| Big-O       | Name          | If n doubles, work…   | Example |
|-------------|---------------|-----------------------|---------|
| O(1)        | constant      | stays the same        | `arr[5]` direct index access |
| O(log n)    | logarithmic   | grows by ONE step     | binary search (halve each time) |
| O(n)        | linear        | doubles               | one loop over the array |
| O(n log n)  | linearithmic  | a bit more than 2x    | good sorting (`.sort()`) |
| O(n²)       | quadratic     | QUADRUPLES            | loop inside a loop |
| O(2ⁿ)       | exponential   | explodes              | naive recursion (DP topic) |

## Reading Big-O off your code
- **Rule 1:** a single loop over the input → **O(n)**.
- **Rule 2:** a loop INSIDE a loop (nested) → **O(n × n) = O(n²)**.  ← the big one
- **Drop constants & smaller terms:** O(2n) → O(n);  O(n² + n) → O(n²).
  Keep only the DOMINANT term (for large n it drowns out the rest).

## ★ HOW TO DERIVE COMPLEXITY (the recipe — don't guess, reason)
**TIME — "count the loops over n":**
1. One loop over input → O(n). 2. Loop inside a loop → O(n²). 3. O(1) work inside (map[x]++,
   .count, arithmetic) adds nothing. Then drop constants: O(n)+O(n)=O(n).
**SPACE — "how big does my EXTRA structure get, worst case?":**
1. Just a few vars (i, max, count) → O(1).
2. A map/array that can grow with input → O(n).
3. A structure bounded by something FIXED (26 letters, 128 ASCII) → O(1).
   ⚠️ Map keys = arbitrary NUMBERS → can grow to n → O(n).
      Map keys = letters (fixed alphabet) → O(1). (This is why #387 was O(1) but #169 is O(n)!)

## Why O(n²) is scary
- n = 10   → ~100 operations
- n = 1,000 → ~1,000,000 operations
- n = 1,000,000 → ~1,000,000,000,000 (a trillion) — too slow.
The whole game in interviews: take an O(n²) brute force and get it to O(n log n) or O(n).

## Space complexity (same idea, for MEMORY not time)
- "How much EXTRA memory grows with n?"
- O(1) space = a few variables, no growth (e.g. brute-force Two Sum).
- O(n) space = a structure that grows with input (e.g. a HashMap holding up to n items).
- Common trade-off: **use more space (O(n)) to save time** (O(n²) → O(n)). ← Two Sum optimal does this.

## Applied: brute-force Two Sum
- Nested loop → **Time O(n²)**, **Space O(1)**.
- Optimal (HashMap) → Time O(n), Space O(n). [see two-sum notes]
