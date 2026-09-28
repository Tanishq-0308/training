# 📝 LeetCode Practice List — matched to YOUR current level

Only problems using patterns you've ALREADY learned: HashMap (existence + counting),
frequency counting, Two Pointers (opposite ends) and Stack (matching). All Easy / Easy-Medium. Solve in C++.
*(Last reviewed 2026-09-23. No new pattern since Stack on 2026-08-30.)*
Mark with [x] when accepted on LeetCode.

> Goal: 2 problems/day. Do the ⭐ ones first (most fundamental / Adobe-relevant).

## ── HashMap: existence lookup (the Two Sum pattern) ──
- [x] #1   Two Sum ⭐ (DONE — accepted)
- [x] #217 Contains Duplicate ⭐ (DONE) — does any value appear twice? (Set/Map)
- [x] #219 Contains Duplicate II (DONE) — duplicate within distance k
- [x] #2351 First Letter to Appear Twice (DONE)

## ── HashMap: frequency counting (the Anagram pattern) ──
- [x] #242 Valid Anagram ⭐ (DONE)
- [x] #383 Ransom Note ⭐ (DONE in cpp) — count magazine up, subtract note, if <0 return false
- [x] #387 First Unique Character in a String ⭐ (DONE in cpp) — count, then find first with count 1
- [ ] #389 Find the Difference — one extra char between two strings
- [~] #169 Majority Element ⭐ — element appearing > n/2 times (solved locally in `day-06`; **submit on LeetCode to tick it**)
- [x] #349 Intersection of Two Arrays (DONE in cpp) — set + erase for dedup
- [ ] #350 Intersection of Two Arrays II — with counts (Map)
- [ ] #1207 Unique Number of Occurrences
- [ ] #771 Jewels and Stones — count jewels in stones (Set)

## ── Stack (LEARNED — LIFO, matching) ──
- [x] #20 Valid Parentheses ⭐ (DONE in cpp) — push openers, match+pop closers, empty at end
- [ ] #1047 Remove All Adjacent Duplicates ⭐ — push, pop if same as top (**NEXT**: file ready in `dsa/day-11/`)
- [ ] #844 Backspace String Compare — stack per string
- [ ] #232 Implement Queue using Stacks

## ── Two Pointers (LEARNED Day 3 — opposite-ends flavor) ──
- [x] #167 Two Sum II - Input Array Is Sorted ⭐ (DONE in cpp) — opposite-ends pointers
- [x] #125 Valid Palindrome ⭐ (DONE in cpp) — left/right converge (skip non-alphanumeric)
- [ ] #344 Reverse String ⭐ — swap ends, move inward
- [ ] #977 Squares of a Sorted Array — opposite ends, fill result from the back
- [ ] #88  Merge Sorted Array — two pointers from the back
- [ ] #11  Container With Most Water (Medium) ⭐ — opposite-ends, move the smaller wall

### Two Pointers — slow/fast flavor (NOT yet taught — try after we cover it)
- [ ] #283 Move Zeroes — slow/fast pointer
- [ ] #26  Remove Duplicates from Sorted Array — slow/fast
- [ ] #27  Remove Element — slow/fast

## How to practice (the right way)
1. Read problem → identify the PATTERN (is this existence? counting? two pointers?).
2. Brute force in your head first → state its Big-O.
3. Optimize → code in C++ → test locally → submit on LeetCode.
4. If wrong: read the FAILING test case, debug yourself before asking.
5. After accepting: note time & space complexity. Move on.

## ⭐ Priority order if short on time (do these 8 first)
217 → 383 → 387 → 169 → 167 → 125 → 344 → 283
