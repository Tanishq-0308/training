# DSA · Lesson 3 — Frequency Counting (+ Valid Anagram)

## ★★ PRINCIPLE: "check EVERYTHING before concluding success" ★★
For any "is EVERYTHING valid?" question (anagram, palindrome, is-sorted, all-positive):
- `return false` EARLY, INSIDE the loop, on the FIRST violation. (safe — one bad = definitely no)
- `return true` ONLY AFTER the loop finishes. (safe only once all checked)
- ❌ NEVER `return true` inside the loop — you'd conclude success after checking just ONE item.
```cpp
for (auto p : m) if (p.second != 0) return false;  // fail fast, inside
return true;                                         // success, ONLY after loop
```
(Bug I made on recovery: `if(...) return false; else return true;` inside the loop → returned
after the FIRST entry. With unordered_map the order is random → NON-DETERMINISTIC wrong answers.)

## HashMap's 2nd superpower: COUNTING
Yesterday: HashMap for "does X exist?" (Two Sum). Today: HashMap as a TALLY counter.
- key = the thing, value = how many times it appears.
- Pattern: `for each item → map[item]++` (in C++, ++ auto-starts missing keys at 0).
- Unlocks: most-frequent element, first non-repeating char, anagrams, etc.

## ★ The "count then scan" two-pass shape (recognize this!)
Many problems = build a frequency map (Pass 1), then scan in ORDER (Pass 2).
Must finish counting BEFORE checking, because at index 0 you don't yet know what repeats later.
Solves: first unique char, most frequent, etc.

### Applied: First Unique Character (#387) — return INDEX of first non-repeating char (-1 if none)
```cpp
int firstUniqChar(string s) {
    unordered_map<char,int> count;
    for (int i=0;i<s.size();i++) count[s[i]]++;        // Pass 1: count
    for (int i=0;i<s.size();i++) if (count[s[i]]==1) return i;  // Pass 2: first with count 1
    return -1;
}
```
- Time **O(n)** (two passes = 2n). Space **O(1)** — map ≤ 26/128 chars, bounded by ALPHABET
  not input. (Don't reflexively say O(n) space for a HashMap — here it's fixed-alphabet → O(1)!)
- `.count` (existence) is NOT enough here — need the FREQUENCY (how many), so use the value.

## Problem: Valid Anagram (LeetCode #242, Adobe-tagged)
Anagram = same chars, same counts, different order. "anagram"/"nagaram" → true.

### Two approaches + their Big-O (know the trade-off!)
- **Sorting:** sort both strings, compare. **O(n log n)** — sorting is the bottleneck.
- **Counting (optimal):** tally chars, compare counts. **O(n)** time, O(n) space. ← beats sorting.
  "Sorting works (O(n log n)) but I can do better with a frequency count in O(n)."

### Algorithm (add-then-subtract trick)
1. **Early exit:** if `s.size() != t.size()` → return false. (different length can't be anagram)
2. Count each char of s: `count[s[i]]++`
3. Subtract each char of t: `count[t[i]]--`
4. If every count == 0 → anagram. Any non-zero → not.

```cpp
bool isAnagram(string s, string t) {
    unordered_map<char,int> count;
    if (s.size() != t.size()) return false;
    for (int i=0;i<s.size();i++) count[s[i]]++;
    for (int i=0;i<t.size();i++) count[t[i]]--;
    for (auto p: count) if (p.second != 0) return false;
    return true;
}
```

### Pro optimization (skip the 4th loop) — mention in interviews
Check negativity DURING subtraction; if lengths equal + nothing goes negative → it's an anagram:
```cpp
for (int i=0;i<t.size();i++) { count[t[i]]--; if (count[t[i]] < 0) return false; }
return true;
```

## ★★ THE BUG I MADE (never repeat) ★★
I wrote `for (auto p : count)` to COUNT the string chars — but count was EMPTY, so it ran 0 times.
**Rule: loop over the STRING to READ input chars (`for i; s[i]`). Loop over the MAP to READ results
(`for auto p : count`). Don't mix them.**
- String chars → index loop `for(int i...) s[i]`
- Map results → range loop `for(auto p : count) p.first/p.second`
