# DSA · Lesson 4 — Two Pointers

## The idea
Use TWO index variables moving through an array intelligently, instead of nested loops.
Often gives O(n) time with **O(1) space** (no HashMap needed). The other big optimization tool
besides the HashMap.

## Flavor 1: Opposite ends (converging) — needs a SORTED array
`L = 0` (start), `R = n-1` (end), move toward each other based on the sum:
- sum **too small** → `L++`  (array sorted → moving right gives a BIGGER value)
- sum **too big**   → `R--`  (moving left gives a SMALLER value)
- sum **== target** → found it!
Each move is a SMART step toward the answer — never a wasted comparison.

### Two Sum II (sorted) — the canonical example
```cpp
vector<int> twoSumSorted(vector<int>& nums, int target) {
    int L = 0, R = nums.size() - 1;
    while (L < R) {                       // loop UNTIL pointers meet
        int sum = nums[L] + nums[R];
        if (sum == target) return {L, R};
        else if (sum < target) L++;       // too small → bigger
        else R--;                         // too big → smaller
    }
    return {};
}
```
**Time O(n), Space O(1).**

## ★ LOOP CHOICE lesson (bug I made)
I first used `for (int i=0; i<nums.size(); i++)` with an UNUSED `i`. Wrong — the STOP
condition must match what actually controls the loop. Here the POINTERS control it, so use
`while (L < R)`. The condition `L < R` IS the termination rule.
- Use `for` → counting a fixed number of times.
- Use `while` → loop UNTIL a condition changes (e.g. pointers meet).

### Applied: Valid Palindrome (#125) — opposite-ends + skip junk
Two pointers from both ends; SKIP non-alphanumeric, compare case-insensitively.
```cpp
while (L < R) {
    while (L < R && !isalnum(s[L])) L++;     // skip junk left (inner while — may skip several)
    while (L < R && !isalnum(s[R])) R--;     // skip junk right
    if (tolower(s[L]) != tolower(s[R])) return false;
    L++; R--;
}
return true;
// Time O(n), Space O(1).
```
**⚠️ Bug I made: `islower` vs `tolower`.**
- `is...` family (isalnum/islower/isdigit/isupper) → ASKS a yes/no question → returns true/false.
- `to...` family (tolower/toupper) → TRANSFORMS → returns a new character.
  Use `tolower` to convert-for-comparison. `islower` would compare two booleans = garbage.
(Both from `#include <cctype>`. Standard-library helpers ARE allowed in interviews — just ask
the interviewer if unsure; they're plumbing, not the algorithm being tested.)

## Flavor 2: Slow / fast pointers (same direction) — to learn next
Both start at the front; one moves faster/conditionally. Used for: Move Zeroes, Remove
Duplicates from Sorted Array, etc. (covered when we do those problems).

## ★★ Two Sum — three ways (know the trade-off cold) ★★
| Version       | Time     | Space | Sorted? |
|---------------|----------|-------|---------|
| Brute force   | O(n²)    | O(1)  | no      |
| HashMap       | O(n)     | O(n)  | no      |
| Two Pointers  | O(n)     | O(1)  | YES     |

Interview line: "Sorted → two pointers for O(1) space. Unsorted → HashMap for O(n) time
without sorting. Sorting just to two-point is O(n log n), so for unsorted input HashMap wins."
