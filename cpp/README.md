# C++ Mastery Track — toward Senior/Production-level C++

Goal: make C++ my **greatest strength** — understand it the way a senior engineer at a
product company (e.g. Adobe) does. Not just DSA syntax — the *language itself*.

## Folder layout
- **`CPP-INTERVIEW-NOTES.md`** ⭐ — **the combined revision file. Revise from this one.**
  Organized by interview question, with 🎯 CUE boxes (answer aloud first), 🎤 SAY THIS
  spoken answers, a rapid-fire drill and a spaced revision schedule. Appended every session.
- `_notes/` — per-lesson notes for FIRST-TIME learning (deeper build-up, one file per topic)
- `exercises/` — small hands-on programs I write while learning each concept

(DSA problems live in `../dsa/`. The C++ *syntax-for-DSA* notes live in `../dsa/_notes/cpp/`.
This track is for the LANGUAGE DEPTH — memory, pointers, RAII, smart pointers, templates, STL, etc.)

## Curriculum (Phase A → B, taught depth-first, applied in DSA)

### Phase A — Foundations the language rests on
- [x] Memory model: stack vs heap, how variables live
- [x] Pointers & references (`*`, `&`, pointer vs reference, `nullptr`)
- [x] `const` correctness; pass by value vs reference vs const-reference
- [ ] Arrays vs vector internals (size vs capacity, why vector grows)

### Phase B — Modern & production C++ (the senior differentiator)
- [x] Classes/OOP: constructors, destructors — (Rule of 0/3/5 still to cover)
- [x] RAII (resource lifetime = object lifetime) — the core senior idea
- [x] Smart pointers: unique_ptr, shared_ptr (vs raw pointers)
- [x] Move semantics: lvalue/rvalue, std::move, why it's fast
- [x] Templates & generics; a peek at how the STL is built
- [~] STL depth: stack/queue/priority_queue done — iterators, map vs unordered_map, algorithms left
- [ ] Concurrency basics: threads, mutex, data races (intro)

## How each concept is learned
Teach the mental model → I predict/write code before the reveal → run it with g++ → apply it in
a DSA problem → I explain it aloud on video (English track). Mark [x] when solid.

Compiler: g++ 10.3.0. Compile: `g++ file.cpp -o file` then `./file`.
