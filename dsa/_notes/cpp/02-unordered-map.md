# C++ for DSA · Lesson 3 — unordered_map (the HashMap)

Same concept as JS `Map`: key → value, O(1) lookup. In C++ it's `unordered_map`.

## Declare (must specify BOTH key and value types)
```cpp
#include <unordered_map>
unordered_map<char, int> count;   // keys are char, values are int. (JS: new Map())
```

## Operations
```cpp
count['a'] = 5;        // store/overwrite              (JS: map.set('a',5))
int x = count['a'];    // read the value               (JS: map.get('a'))
count['a']++;          // increment
count['a']--;          // decrement
count.count('a');      // EXISTENCE: 1 if key exists, 0 if not  (JS: map.has)
for (auto p : count) { // loop all pairs
    // p.first = key, p.second = value
}
```

## ★ The counting magic (why C++ is great for frequency)
Accessing a MISSING key with `[]` auto-creates it with the DEFAULT value (0 for int).
So on an empty map:
```cpp
count['a']++;   // 'a' missing → created as 0 → ++ → 1.  No "does it exist?" check needed!
```
JS needed `if(map.has(k)) map.set(k,map.get(k)+1) else map.set(k,1)`. C++ = just `count[k]++`.

## ⚠️ THE #1 TRAP: [] always creates the key (even when just READING)
```cpp
cout << m['c'];     // if 'c' was missing, this CREATES it as 0!
m.count('c');       // now returns 1 — because reading m['c'] above inserted it
```
- `m[key]`  → gives the VALUE (default 0 if missing) AND inserts the key.
- `m.count(key)` → gives EXISTENCE (1/0) WITHOUT inserting. Use this to check safely.
- To check existence without side effects: use `.count()` or `.find()`, NEVER `m[key]`.

### VALUE vs EXISTENCE (a key can exist WITH value 0!)
`.count(k)` checks whether the KEY EXISTS — the stored VALUE is irrelevant.
```cpp
m['k'] = 0;       // key 'k' exists, value is 0
m['k']        // → 0  (the value)
m.count('k')  // → 1  (key EXISTS — value 0 doesn't matter!)
m.count('z')  // → 0  (never added)
```
Why this matters: `m['k']` returning 0 is AMBIGUOUS — "exists with value 0" OR "didn't exist,
just created it as 0"? Can't tell. That's why `.count()` is the unambiguous existence check.

## ⚠️ "unordered" = does NOT keep insertion order
Output order is arbitrary (unlike JS Map which keeps insertion order). Fine for counting/lookup.
If you need keys sorted: use plain `map` instead (slower, O(log n) ops). Default to unordered_map.

## Verified I understand
- m['a']++ twice = 2 ✓, m['b']=10 then -- = 9 ✓
- m['c'] never set = 0 (missed: said 1 — it's the VALUE 0, not existence) — corrected
- .count existing = 1 ✓
- TRAP: reading m['c'] made .count('c')=1 afterward — got this right ✓
