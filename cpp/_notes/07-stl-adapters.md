# C++ Mastery · Lesson 7 — STL Adapters: stack / queue / priority_queue

Ready-made containers; handle their own memory (RAII). Core DSA tools.

| Adapter          | Order        | Add    | Peek    | Remove | Use for              |
|------------------|--------------|--------|---------|--------|----------------------|
| stack            | LIFO         | push   | top     | pop    | brackets, DFS, undo  |
| queue            | FIFO         | push   | front   | pop    | BFS                  |
| priority_queue   | MAX first    | push   | top     | pop    | top-K, scheduling    |

## stack — LIFO (last in, first out) `#include <stack>`
```cpp
stack<int> s; s.push(1); s.push(2);  // 2 on top
s.top();  // 2 (peek)     s.pop();  // remove top
s.size(); s.empty();
```

## queue — FIFO (first in, first out) `#include <queue>`
```cpp
queue<int> q; q.push(1); q.push(2);  // front[1,2]back
q.front();  // 1 (peek)   q.pop();  // remove front
```
BFS uses this.

## priority_queue — HEAP, always MAX on top (the one JS lacked) `#include <queue>`
```cpp
priority_queue<int> pq; pq.push(3); pq.push(9); pq.push(1);
pq.top();  // 9  ALWAYS the max, regardless of push order
pq.pop();  // removes the max
```
- push/pop = O(log n), top = O(1). Default = MAX-heap.
- MIN-heap: `priority_queue<int, vector<int>, greater<int>>` (smallest on top).
- Unlocks: top-K, Dijkstra, median.

## ⚠️ Gotcha: pop() removes but does NOT return the value.
Use top()/front() to READ, THEN pop() to remove. Two calls.
```cpp
int x = s.top(); s.pop();   // correct way to "pop and use"
```

## Bonus: ONE function for stack/queue/priority_queue → use a TEMPLATE
They're 3 different TYPES, so a normal function can't take all. A template can (any type with .push()):
```cpp
template <typename T>
void pushThree(T& c) { c.push(1); c.push(2); c.push(3); }
// pushThree(s); pushThree(q); pushThree(pq);  all work
```
Templates = code that works for ANY type supporting the ops used. The whole STL is templates
(stack<int>, vector<int>, map<...> — the <> IS a template). Full lesson: templates.
