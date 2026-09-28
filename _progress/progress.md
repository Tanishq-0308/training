# Adobe Prep — Progress Log

## Phase P1 — JavaScript Mastery

### ✅ Lesson 1: Scope, Hoisting & Closures  (Session 1)
- Scope, scope chain, block vs function scope (var/let/const) — got it
- `undefined` (value) vs `ReferenceError` (no such var) — got it (corrected once)
- Hoisting + Temporal Dead Zone (TDZ) — got it, 4/4 on quiz
- Closures: definition, private state, factory pattern — got it
  - MISSED then corrected: two counters do NOT share state (new scope per call)
- The `var`/`let` loop trap (3 3 3 vs 0 1 2) — initially fuzzy, re-taught with "box" model, now solid
  - Key: trap = var + DELAYED execution. Either ingredient removed → no surprise.
- Homework: `createBankAccount` closure w/ private balance + guard clause — DONE, correct
  - Used early-return guard clause (good instinct)
  - Interviewer follow-ups learned: signal success/failure explicitly; validate negative input
- Notes: p1-javascript/_notes/01-scope-hoisting.md + 01b-closures.md

### Decisions
- Teaching: Socratic + hands-on (predict/write before reveal)
- DSA: JS primary (R1 tests DSA+JS) + C++ as deliberate second track (career edge; Adobe is C++)

## Phase P5 — DSA

### ✅ Day 1: Big-O + HashMap + Two Sum  (Session 1)
- Big-O time complexity: O(1)→O(log n)→O(n)→O(n log n)→O(n²)→O(2ⁿ) — got it
  - Rule 1: single loop = O(n). Rule 2: nested loop = O(n²). Drop constants/smaller terms.
  - Quiz: nested loop = O(n²) ✓; n=1000 → 1,000,000 ops ✓
- Space complexity + space-for-time trade-off — got it
- HashMap (JS Map): set/get/has/delete, O(1) lookups — got it
  - Pattern learned: "brute force slow because it SEARCHES → replace scan with HashMap"
  - Sharp Q from user: array vs Map space — both O(n); Map wins on O(1) lookup. Understood.
- Two Sum: wrote brute force O(n²) AND optimal HashMap O(n) — both run & pass ✓
  - Dry-ran [3,2,4] correctly in head before coding
- Learned the interview narration arc: clarify → brute force → bottleneck → optimize → verify
- Notes: dsa/_notes/concepts/00-big-o-complexity.md + 01-hashmap-two-sum.md
- TODO (optional): re-solve Two Sum in C++ (second-track language)

## C++ for DSA (development=JS, DSA=C++ — settled this session)

### ✅ C++ Lesson 1–2: basics + vector  (Session 1)
- g++ 10.3.0 installed & working. Compile: `g++ f.cpp -o f` then `./f`.
- Program skeleton (int main, cout/endl, semicolons), types (int/double/char/bool/string) — got it ✓
- vector: .size(), nums[i], push_back() — wrote & ran, all 4 tasks correct ✓
- Insight landed: C++ for DSA = same logic as JS, just syntax (types, .size, compile step)
- Notes: dsa/_notes/cpp/01-cpp-basics-vector.md

---

### ✅ Day 2: Frequency Counting + Valid Anagram (in C++)  (Session 2)
- WARM-UP RECALL (from memory, no notes): loop trap 3 3 3 ✓, Two Sum O(n²)→O(n) ✓,
  why HashMap beats array scan ✓ — retained everything from Day 1. Revision working.
- New concept: HashMap as a COUNTER (key→count). 2nd superpower after existence-lookup.
- Sorting O(n log n) vs counting O(n) trade-off — user reasoned to counting themselves ✓
- Designed Valid Anagram algorithm themselves: early exit on length, add s / subtract t, check 0s ✓
- Taught C++ unordered_map FROM SCRATCH (user asked — didn't know it):
  declare <K,V>, [] access, ++/-- counting magic (auto-0), .count() existence, range loop.
  - Quiz 4/5. Missed: m['c'] on missing key = 0 not 1 (value vs existence). Corrected.
  - Got the TRAP right: reading m['c'] inserts it → .count('c')=1 after. (#1 C++ map trap)
- Wrote Valid Anagram in C++. BUG hit: used `for(auto p:count)` (empty map!) to count string chars.
  Fixed → loop STRING to read chars, loop MAP to read results. Runs, all tests + edge cases pass ✓
- Pro tip learned: check negativity inline to skip the final pass.
- Notes: dsa/_notes/concepts/02-frequency-count-anagram.md + dsa/_notes/cpp/02-unordered-map.md

### ✅ P1 Lesson 2: The Event Loop  (Session 2, after anagram)
- Single thread / call stack / Web APIs / callback queue / event loop — restaurant analogy landed
- setTimeout(fn,0) ≠ "run now" — runs after sync done + stack empty. Connected back to loop trap.
- Macrotask (setTimeout) vs Microtask (Promise) queues; rule: sync → ALL micro → then macro
- Quiz results (ALL CORRECT, including boss level):
  - A C B (setTimeout 0) ✓
  - 1 4 3 2 (promise beats setTimeout) ✓
  - A F C E B D (boss: setTimeout inside a promise; B before D via FIFO macro queue) ✓ ✓
- Strong topic for them — genuinely R1-passing level on event loop.
- Notes: p1-javascript/_notes/02-event-loop.md

### ✅ Day 3: C++ Two Sum (HashMap) + Two Pointers  (Session 3)
- WARM-UP RECALL: event loop X W Z Y ✓, anagram O(n) vs sort O(n log n) ✓, closure def ✓,
  map[] vs .count() trap ✓ — then asked sharp Q: .count returns 1 even if value is 0 (key exists!) ✓
- Closed the Day-1 gap: wrote Two Sum (unsorted) in C++ with unordered_map. Local pass ✓
- ★ BIG BUG on LeetCode (61/63): used unordered_map<CHAR,int> for NUMBER keys → char overflows
  (~-128..127), big nums [1,6142,8192,10239] wrapped → WA. Fix: <int,int>. Lesson: match key type
  to data; C++ types have SIZE LIMITS (JS hides this); ALWAYS test on real judge. (note updated)
- Learned TWO POINTERS (opposite-ends flavor, needs sorted): Two Sum II in C++.
  - Bug: used `for(i...)` with unused i → wrong stop condition. Fixed to `while(L<R)`.
  - Lesson: loop condition must match what controls iteration (pointers → while L<R).
- Two Sum THREE WAYS trade-off table internalized (brute O(n²)/O(1), map O(n)/O(n), 2ptr O(n)/O(1)+sorted)
- Solved solo on LeetCode: #217, #219, #2351, #167. Total accepted: #1,#217,#219,#2351,#242,#167.
- Notes: dsa/_notes/concepts/03-two-pointers.md. Practice tracker: dsa/PRACTICE-LIST.md (kept current).

### ✅ P1 Lesson 3: Promises & async/await  (Session 4, JS part)
- WARM-UP: 2ptr R-- when too big ✓, char range ✓, micro>macro ✓; MISSED ++c vs c++ (said 0 1 0,
  actual 1 2 1) — learned: ++c change-then-give, c++ give-then-change. Note added.
- Promises: 3 states (pending/fulfilled/rejected), receipt analogy. Stuck on new Promise/resolve —
  taught from scratch: resolve = the "DONE!" button JS hands you; resolve(X) → X flows to .then(X).
  Why resolve not return: can signal done LATER (inside setTimeout). Demo run, clicked. ✓
- async/await: async fn returns Promise; await pauses fn (not program) until resolve.
- ORDERING quizzes ALL CORRECT: `1 2 4 3` (executor sync, .then micro) ✓; `A B D C`
  (before-await sync, after-await microtask) ✓. Full chain understood: callbacks→Promises→async/await→microtask queue.
- Backlog for later: Promise.all/race, try/catch errors, real fetch.
- Notes: p1-javascript/_notes/03-promises-async-await.md

### ✅ DSA Day 4: Valid Palindrome (#125) — pattern RECOGNITION focus  (Session 4)
- Strategy chosen by user: MASTER known techniques before adding new ones (good call — depth>breadth).
- User RECOGNIZED two-pointers themselves (no hint) + designed full algo incl. skip-junk logic ✓
- Asked great meta-Q: "are library helpers allowed in interviews?" → yes (plumbing, not the algo);
  ask interviewer if unsure. Taught the allowed-vs-defeats-the-purpose line.
- Tools: isalnum/tolower (<cctype>). BUG: used islower (asks) instead of tolower (transforms) →
  all answers wrong. Fixed. Lesson: is...=yes/no, to...=transform. Note added.
- Also taught MANUAL versions via ASCII (chars are numbers; case differs by 32) for "no library" asks.
- Time O(n), Space O(1). LeetCode #125 marked done in tracker.
- Accepted so far: #1,#217,#219,#2351,#242,#167,#125 (7 total).

### ✅ Session 5: async clarity + First Unique Char (#387)
- WARM-UP 5 Qs: async order 1 2 4 3 ✓, c++/++c → 5,7 ✓, 2ptr L++ ✓; SHARPEN NEEDED:
  is-vs-to *difference* (they only said "use tolower"), char range (keeps saying -127..128; it's -128..127).
- ★ User asked a deep async Q → taught "await pauses the FUNCTION not the PROGRAM" (waiting≠freezing).
  Then THEY realized: everything after await waits even if it doesn't need the value → led to the
  Promise.all / "start independent work first" optimization. Strong reasoning. Notes updated.
- DSA #387 First Unique Char: recognized COUNTING pattern (corrected: needs FREQUENCY not .count
  existence). Understood the two-pass "count then scan in order" shape. Built it themselves, all tests pass.
  - Great complexity point: space is O(1) (alphabet-bounded ≤26/128), NOT O(n). Time O(n).
- Accepted so far: #1,#217,#219,#2351,#242,#167,#125,#387 (8 total).

### ✅ Session 6 (2026-06-12): Promise depth + Majority Element (partial)
- Promise.all/allSettled/race + try-catch taught. all = all-or-nothing (await line THROWS, results
  never assigned); allSettled = never rejects; race = first settles. Trap quiz understood. Notes updated.
- Warm-up sharpen items CLOSED: is-vs-to difference ✓, char range -128..127 ✓.
- Majority Element (#169): HashMap approach, TAUGHT complexity-derivation recipe (count loops / how big
  does structure get). Time O(n) Space O(n) — derived, not guessed. Recipe saved to 00-big-o note.
  - Bug: threshold check only in `if` branch not `else` → [1] returned -1. Fixed by removing redundant
    if/else (map[]++ works for new keys) + unconditional check. All edge cases pass.
- Was mid-teaching Boyer-Moore voting (O(1) majority) when session ended.

### ✅ Session 7 (2026-07-31): RECOVERY after ~7-week gap
- User feared forgetting everything. DIAGNOSTIC: scored ~5.5/6 on concept recall! Closures, event loop,
  async, two-pointers, Big-O all retained. Only gap: map[] trap (refilled) + C++ SYNTAX muscle memory.
- Re-solved Valid Anagram from blank file after a one-card unordered_map syntax refresher. Fingers came back.
  - Hit + fixed 2 classic bugs: early `return true` inside loop (non-deterministic!), and wrong final return.
  - LEARNED NEW PRINCIPLE: "check everything before concluding success" — return false inside loop,
    return true only AFTER. Saved to notes. Applies to anagram/palindrome/is-sorted/all-valid.
- VERDICT: fully recovered, faster than expected. Proper first-time learning → durable memory.

### 🔀 PLAN PIVOT (2026-07-31) → Plan v2: Senior C++ first
- User revealed the 7-week gap was spent learning BACKEND + Next.js (real projects) — continues on side.
- NEW primary goal: **C++ at senior/production depth** (their greatest strength) + DSA (alternate
  concept→apply). Backend/Next.js self-driven on side. JS/TS interview prep LATER. English track added.
- Full plan: C:\Users\sharm\.claude\plans\have-a-change-in-woolly-floyd.md + memory project-plan-v2-cpp-first.
- New session shape: warm-up → C++ language concept (hands-on) → DSA applying it → assign English
  recording topic. Cadence: few ~45-60min sessions/week.
- Workspace added: cpp/ (language-depth track, README has curriculum checklist), english/SPEAKING-LOG.md.
- Boyer-Moore DEFERRED (agreed — trick, not a pattern; foundations first).

### ✅ C++ Mastery Lesson 1 (2026-07-31): Memory Model — stack vs heap
- User chose "start C++ from scratch" (no diagnostic) — good for senior-depth rebuild.
- Taught stack (auto/fast/small/dies-with-function) vs heap (manual/slower/large/until-delete).
- ★ Key insight landed: pointer and its target live in DIFFERENT places. p on stack, `new` value on heap.
  User REASONED this themselves (Q2). Memory leak = lost the only pointer to heap mem.
- Great curiosity Q from user: "int* a = 10?" → taught it's an ERROR (pointer holds ADDRESS not value).
  Showed compiler error. Valid ways to set a pointer: &var, new, nullptr. `*` in decl vs deref explained.
- Exercise 01-stack-heap.cpp: user wrote it correctly (new/*/delete). RAN it — addresses PROVED the
  concept: &heapVar (stack, next to stackVar) vs heapVar's target (heap, far away). Saw it live.
- Notes: cpp/_notes/01-memory-model-stack-heap.md
- ENGLISH topic assigned: explain stack vs heap + what a memory leak is (SPEAKING-LOG.md row 1).

### ✅ C++ Mastery Lesson 2 (2026-08-07): References vs Pointers
- WARM-UP 4/4 from memory (post-gap): stack/heap lifetime ✓, p-on-stack/value-on-heap ✓, all 3
  why-heap reasons ✓, reasoned about their OWN makeCounter experiment (heap return = safe) ✓.
  Added: heap-returning fn = OWNERSHIP TRANSFER (caller must delete) → foreshadows smart pointers.
- User had been experimenting solo (makeCounter, cin>>n arr[n]) — good self-driven learning.
- Reference = ALIAS (another name for same memory). int& r = x. Nickname analogy.
- Pointer vs reference table taught: ref can't be null, can't be reseated, used directly.
- ★ Trap NAILED: `r = b` does NOT reseat r → assigns b's value into a (a=10). Output 10 10 10.
  Reasoned it correctly themselves. Rule: assignment thru ref always hits the aliased var's value.
- ★ Practical payoff: pass-by-value COPIES (slow/can't modify original) vs pass-by-reference ALIASES.
  THIS is why DSA used vector<int>&. Exercise 02-references.cpp: addTenByValue (n stays 5) vs
  addTenByReference (n→15) vs swap (p,q actually swapped). All correct, ran, saw it live.
- Notes: cpp/_notes/02-references-vs-pointers.md
- ENGLISH topic to assign: explain pointer vs reference (3 differences) OR why swap needs references.

### ✅ C++ Mastery Lesson 3 (2026-08-08): const-correctness
- WARM-UP 4/4 from memory. Sharpened Q3: pass-by-ref has TWO benefits — modify original AND avoid
  expensive copy (perf). The "read big data without copying" need → segues into const&.
- Recorded BOTH prior English videos (stack-vs-heap, pointer-vs-reference) ✓✓ — consistent! Log updated.
- const = "cannot change" = promise to compiler → runtime bug becomes COMPILE error (caught early).
- ★ const T& = idiomatic read-only param: `&` no copy + `const` can't modify. Senior default for
  non-trivial read-only params. Decision table taught (value / ref / const-ref).
- Predict quiz A/B/C: got B,C perfect. A corrected: pass-by-value modifies the COPY not caller's
  original (tied back to addTenByValue). Now crisp.
- ★★ GREAT user question: "vector<int>& v already gives original — why int& x in the loop too?"
  Taught: references don't cascade. vector<int>& = don't copy the CONTAINER; `for(int x:v)` still
  COPIES each element; need `int& x` to alias elements. PROVED with copy-vs-ref demo (1 2 3 vs 2 3 4).
  Bonus: `for(const auto& x : v)` = idiomatic read-only loop.
- Exercise 03-const.cpp: printAll(const&) + addOne(int& x) both work (1 2 3 → 2 3 4). Then Task C:
  compiled `v.push_back` inside const& → COMPILE ERROR ("discards qualifiers"). Saw const enforce.
- Notes: cpp/_notes/03-const-correctness.md
- ENGLISH topic to assign: explain const-correctness — why `const vector<int>&` and what bug it prevents.

### ✅ C++ Mastery Lesson 4 (2026-08-08): Classes, ctor/dtor → RAII intro
- WARM-UP 4/4 again. Recorded const-correctness video (OBS+cam+Excalidraw+live compiler) — 3/3 videos.
- Class = data+methods. Ctor = auto setup on create; dtor = `~` auto cleanup on destroy.
- ★ KEY: stack object's dtor runs AUTOMATICALLY at scope `}`, guaranteed (even on exception).
  Predicted Widget output start/constructed/inside block/destroyed/end perfectly (dtor before end).
- ★★ RAII intro: wrote IntBox (new in ctor, delete in dtor). main NEVER calls delete → dtor frees
  automatically. Leak from Lesson 1 now IMPOSSIBLE. "vector/string/unique_ptr are all RAII."
- Notes: cpp/_notes/04-classes-ctor-dtor.md
- ENGLISH topic to assign: explain RAII — what it is, how ctor/dtor make cleanup automatic & leak-proof.

### ✅ C++ Mastery Lesson 5 (2026-08-21): Smart Pointers
- WARM-UP 4/4 after 11-day gap — RAII HELD. Explanations getting more complete (good for English track).
  Minor: spelling (destructor/initialization) for videos; "scope ends" > "function destroyed" for dtor timing.
- unique_ptr = default, ONE owner, make_unique, auto-delete at scope, CAN'T be copied (deleted copy
  ctor → prevents double-delete). Predicted both snippets correctly (auto-delete + copy error).
- shared_ptr = multiple owners, ref-counted (use_count), freed at 0. make_shared. Google-Doc analogy.
- Decision rule: unique_ptr default / shared_ptr when truly shared / raw ptr = borrow only.
  Modern rule: NEVER raw new/delete → make_unique/make_shared.
- Exercise 05: wrote it (missed use_count line, added). Ran → owners: 2 (ref count visible). WROTE IT
  from blank per the coding rule. ✓
- Notes: cpp/_notes/05-smart-pointers.md
- Modern memory story now COMPLETE: raw ptr → RAII → unique_ptr → shared_ptr.
- ENGLISH topic to assign: explain unique_ptr vs shared_ptr — one owner vs shared/ref-count, why no raw new/delete.

### ✅ DSA reactivation (2026-08-21): Contains Duplicate (#217 re-solve)
- Switched to DSA per "alternate" plan (C++ ran 5 lessons straight). DSA had gone cold ~weeks.
- User: "forgot the DSA lessons" + "not sure I can write the code, forgot unordered_map syntax."
  → Same recovery pattern: CONCEPTS held, SYNTAX faded. Refreshed the 4 patterns in 60s from their
    own notes + gave a HashSet syntax card (unordered_set: .count, .insert).
- Re-solved #217 from the card — WROTE IT THEMSELVES, correct, ran (1,0). Reactivated in minutes.
  - Used .count (avoided [] trap) + check-before-insert (same as Two Sum). Time O(n) Space O(n).
  - Polish noted: `return true` makes `else` unnecessary (return-exits, same as majority bug).
- ★ LESSON: DSA fades FASTER than C++ when untouched. Must INTERLEAVE — don't let DSA sit 5 sessions.
- ENGLISH topic still owed from L5: explain unique_ptr vs shared_ptr.

### ✅ DSA (2026-08-21 cont.): Ransom Note (#383) — frequency counting
- WARM-UP: Q1 concept ✓ (refilled: METHOD is .count, not map[]), Q3 O(1) alphabet ✓, Q4 unique_ptr ✓.
  Q2 SYNTAX GAP: forgot the `count[c]++` idiom → refilled (auto-0 then ++, no exist-check needed).
- ★ Great teaching moment: user described ANAGRAM logic (counts must be EQUAL) for ransom note.
  Corrected: ransom note needs ENOUGH (>=), not equal. "aa"/"aab"=true though counts differ.
  Also their length-check would be wrong here (magazine usually longer). Lesson: read problem, don't
  pattern-match blindly.
- RE-TAUGHT the complexity recipe (they forgot again — Q3 said "I forget how"): TIME=count loops,
  SPACE=how big structure grows (n items=O(n), fixed alphabet=O(1)). They then stated #383 = O(n)/O(1).
- Wrote #383 themselves from corrected approach: count magazine++, note--, if <0 return false. Ran 1,0,0 ✓.
- Practice tracker: #383 marked done. (Bookkeeping: #169 solved session 6 but shows unchecked.)
- COMPLEXITY RECIPE keeps fading — drill it in warm-ups until automatic.

### ✅ C++ Mastery Lesson 6 (next session): Move Semantics (std::move)
- WARM-UP: complexity recipe FINALLY sticking (Q1 recalled unprompted, much better!). count[c]++ ✓,
  ransom <0 ✓. Q4: correctly said can't copy unique_ptr but WRONGLY said use shared_ptr to transfer
  → corrected: you MOVE it (std::move), still one owner. Teed up the lesson perfectly.
- Copy (duplicate, expensive) vs Move (steal internals, source emptied, cheap). Photocopy vs hand-over.
- std::move = marks a source as OK-to-steal (doesn't move by itself). unique_ptr: can't copy, CAN move.
- lvalue (named/reusable) vs rvalue (temporary/disposable) — light touch.
- Predicted move quiz correct (1, 42). Exercise 06-move.cpp written themselves: unique_ptr move (1,99) +
  vector move (3,0 — v emptied). Ran ✓. Key generalization: move is GENERAL (vector/string too), not
  just unique_ptr. Style note given: std::move is the proper spelling (they used bare move()).
- Notes: cpp/_notes/06-move-semantics.md
- Modern resource story now COMPLETE: RAII → smart pointers → move. Copy to duplicate, move to hand off.
- ENGLISH still owed: unique_ptr vs shared_ptr (now could add: + move to transfer).

### ✅ DSA (2026-08-26): Intersection of Two Arrays (#349) — Set
- Recorded English video #4 (unique vs shared ptr + move) — CLEAR, well-structured. Spoken clarity
  visibly improving. Log updated (4 recordings).
- WARM-UP 4/4. ★ Complexity recipe NOW LOCKED (recalled unprompted + correctly). Q4 smart-ptr answer
  was teaching-level depth. Drilling paid off — can ease off drilling it now.
- #349: user designed the approach THEMSELVES incl. a dedup trick (set map value to 0). Taught cleaner
  variant: set + s.erase(x) to dedup. New tool: unordered_set.erase(). Wrote it, ran (2 / 9 4) ✓.
- Complexity precision taught: TWO inputs → Time O(n+m) not just O(n). Space O(n).
- Tracker: #349 done.
- ENGLISH owed cleared (recorded). Next topic TBD from next lesson.

### ✅ C++ Mastery Lesson 7 (2026-08-26): STL Adapters — stack/queue/priority_queue
- WARM-UP 4/4. Q2 (RAII) was a complete precise answer. Retention rock-solid; complexity recipe locked.
- stack (LIFO, top/pop), queue (FIFO, front/pop), priority_queue (max-heap, top/pop — the heap JS lacked).
  Gotcha taught: pop() removes but doesn't RETURN — top()/front() then pop().
- Predicted 30 20 10 | 9 correctly. Exercise 07: wrote all 3 drain loops, ran 3 2 1 / 1 2 3 / 7 4 3 1 ✓.
- ★ USER ASKED: "one function to push to all three?" → led straight into TEMPLATES. Showed
  `template<typename T> void pushThree(T&)` working on all 3. They invented the motivation for templates
  themselves. Noted whole STL is templates (<> = template). Templates queued as next full lesson.
- Notes: cpp/_notes/07-stl-adapters.md (incl. template bonus).
- ENGLISH topic to assign: explain stack vs queue vs priority_queue (LIFO/FIFO/max-heap + a use for each).

### ✅ DSA (2026-09-09): Valid Parentheses (#20) — first STACK problem
- Spanned a few short sessions w/ gaps. Taught stack-matching pattern (couldn't see it cold; walked
  "{[]}" valid + "([)]" invalid traces → clicked).
- ★ User asked to write the WHOLE function themselves (no scaffold) → logged permanent preference
  (feedback-teaching-style: BLANK FILES, interview-style; don't put answers in comments).
- First attempt PASSED all 6 given tests but had 2 HIDDEN bugs (adversarial test exposed):
  1. mismatched closer not rejected → "(])" wrongly true. 2. st.top() on empty stack → SEGFAULT on ")".
  Root cause: only handled happy/match path, no failure cases.
- Explained via char-by-char trace (confused at first). They RESTRUCTURED correctly themselves: closer
  branch → if(empty) return false; match→pop; else return false. Both fixed, ran clean.
- KEY LESSON: handle EVERY failure case, not just happy path (working-looking vs correct) = R3 skill.
- Polish: stack<int>→stack<char>. Time O(n) Space O(n). Tracker: Stack section added, #20 done.

## ⏭️ ~~NEXT SESSION agenda~~ (SUPERSEDED — see the latest agenda at the bottom)
1. Warm-up: stack-matching recall + complexity + a C++ item (RAII/move).
2. Pick: (a) C++ Lesson 8 = TEMPLATES (user primed, wrote-the-motivation themselves), OR (b) one more
   stack DSA (#1047 / #844). Lean (a) templates — stack is warm, templates waited 2 sessions.
3. Assign English topic (stack vs queue vs pq still owed). BLANK FILES from now on (no scaffolds).
- (Backend/Next.js on user's side — not our focus.)

---

## 2026-09-10 — Combined notes overhaul + C++ Lesson 8: TEMPLATES

### Warm-up recall
- stack/queue top vs front → ✅ correct ('c' / 'a')
- Valid Parentheses complexity O(n)/O(n) → ✅ correct (reasoning covered time; space reason needed prompting)
- **RAII → ❌ could not recall the full form.** Gap identified: RAII was taught inside Lessons 4+5
  but never written up under its own heading, so it was unfindable for revision.

### User request: ONE combined notes file
> "there are so many md files for cpp notes, we should have a combine file ... and make it more
> readable and easy to understand and with words and sentences should say in the inteview"

Created **`cpp/CPP-INTERVIEW-NOTES.md`** — the single revision file. Then user asked me to check
online for best practice; researched the retention literature and revised the structure again.

Structure (now evidence-backed):
- **🎯 CUE box per section** (Cornell cue-column) — questions only, answer aloud BEFORE reading.
  Research: active recall + spacing are the two strongest findings; Cornell is the most-researched format.
- **"Never revise by reading"** rule at the top — reading produces a *fluency illusion*.
- **🎤 SAY THIS** blocks — literal spoken sentences, full prose. Targets the English weakness directly.
- Organized by **the question an interviewer asks**, not lesson number.
- Rapid-fire recall table (24 Q→A), ⚠️ gotchas, **vocabulary table** (weak phrasing → senior phrasing),
  spaced revision schedule (same day / +3d / +1w / +3w).
- RAII now has its own full section (#5) with the deterministic-destruction keyword.
- **Decided against Anki/flashcards** despite the evidence — user has had 2 multi-week gaps; a daily
  review app becomes a guilt backlog. CUE boxes + rapid-fire give the same mechanism, no new habit.
- Saved as memory `feedback-combined-interview-notes` → append EVERY session.

### C++ Lesson 8 — Templates ✅
Motivated 2 sessions ago by the user's own question (one push function for all 3 adapters).

Taught: the duplication problem → why C++ needs compile-time types (emits machine code; different
types = different CPU instructions) → `template <typename T>` → **instantiation** → **zero-cost
abstraction** → where `T` goes → compile-time duck typing.

**User answers:**
- "how many things differ" → vague (said int/double *ranges*); redirected to the code text (3 words)
- "what does C++ need that JS doesn't" → ✅ "the type of the parameter"
- "how many functions in the binary" → ✅ two
- "is it slower" → ✅ "recipe the compiler uses, zero runtime cost"
- "when does a missing method fail" → ✅ compile time

**Exercise `cpp/exercises/08-templates.cpp`** (blank file, user wrote everything but main):
- `maxOf` → ✅ **correct first try**, no help needed
- `printAll` → wrote `printAll(T value)` → T deduced as `vector<int>` → `cout << (whole vector)` error.
  Said "don't understand" → re-taught with the deduction matching laid out visually
  (`vector<T>` vs `vector<int>` → T=int). Then correct.
- Iterated: missing spaces → missing endl → missing `const`. Each fixed after a targeted question.
- Final polish by me: `for (T i : v)` → `for (const T& i : v)` (copies each element; in a template
  T could be huge). Same mechanism as their Lesson 2 bug, opposite symptom.
- Verified: `7 / 2.5 / zebra / 1 2 3 / hello world` ✅

Also answered their original motivating question — `pushThree(T& c)` where T = the whole container,
contrasted against `printAll(const vector<T>&)` where T = the element. **The contrast is the lesson.**

### Teaching notes
- "don't understand" twice this session → both times the fix was **showing the mechanism visually**
  (the deduction match), not restating the rule. Keep doing that.
- The `const` omission recurred (had `&`, dropped `const`). Watch for it — half-applying Lesson 3.
- Reading template error messages taught as an explicit skill: **first two lines only.**

### English
Recording still owed (stack vs queue vs priority_queue). User: "not able to record the video now" —
did not push. Templates gives a second option now.

## ⏭️ ~~NEXT SESSION agenda~~ (SUPERSEDED — see the latest agenda at the bottom)
1. Warm-up: **RAII full form + one-liner** (failed today — must re-ask), plus templates recall
   (instantiation / zero-cost / where T goes).
2. **DSA is due** — 5 C++ lessons since Valid Parentheses only if we skip; actually 1 since. Do a
   stack problem: #1047 Remove All Adjacent Duplicates or #844 Backspace String Compare.
3. Then C++: Rule of 0/3/5, OR vector internals (size vs capacity — pairs well with templates
   since vector IS a template), OR iterators.
4. Start using the CUE boxes for warm-ups — read the box, user answers aloud, then check.
5. English topic owed. BLANK FILES always.
- (Backend/Next.js on user's side — not our focus.)

---

## 2026-09-12 → 2026-09-23 — Project 1 (text editor), Steps 1–3 + a teaching regression
*(Written up on 2026-09-23. These sessions had not been logged at the time.)*

### What was built: `cpp/projects/text-editor/`
| Step | What | Who wrote it | Bugs hit (all fixed) |
|---|---|---|---|
| 1 Buffer | `insert` / `remove` (clamped) / `getText() const` / `size() const` | User | `substr(0,n)` *kept* n chars instead of removing them. **User found `erase` by searching online.** Signed/unsigned `.size()` comparison → `-Wall` warning → `(int)` cast + `n <= 0` guard |
| 2 InsertCommand | stores the text; `execute` inserts it, `undo` removes `text.size()` | User | Stray debug prints in `main` only |
| 3 DeleteCommand | stores `count` + the deleted text; `undo` re-inserts it | User | (a) saved the WHOLE buffer instead of the last `count` chars → `substr(size - count)`; (b) `remove(10)` on "Hi" → `size - count` wrapped unsigned → `std::out_of_range` crash → clamp `count`; (c) used `text` (Buffer's private member) instead of `b` |
| Split into files | `include/*.h` + `src/*.cpp`, `#pragma once`, `Class::`, `-Iinclude` | **Mostly Claude** (dictated) | Copying across brought back the old unfixed `execute` → re-applied the fix |
| Command base | `Command` with pure virtual `execute`/`undo` + virtual destructor; `: public Command` + `override` | **Claude gave the code; user wired it in** | `override` missing at first → added |
| 4 Editor | `Editor.h` created | — | **Empty file. Step 4 not started.** |

Build: `g++ -Wall -Iinclude src/*.cpp -o editor` → clean, output `[Hello] [He] [Hello] []`.
Old single-file versions were moved to `text-editor/_early/`.

### Good signs
- Every design decision in Step 1 was made by the user: `string` storage, clamping on over-remove, `const string& getText() const`.
- **Found `std::string::erase` without help.** That's the real skill: know what you need, then find the tool.
- Asked sharp questions: "why `Buffer&` and not a pointer?", "where is `unique_ptr`?", "how do we test this?", "why a pointer in the stack?"

### Regression: teaching quality dropped (user flagged it twice)
- **09-18:** "the study method ... is not better than before ... things have degraded." Cause: top-down architecture dumps (Buffer + Command + polymorphism + `unique_ptr` + two stacks at once) and a confusing invented example (`remove(5)`). Saved `feedback-small-steps-not-architecture` to memory.
- **09-22/23:** "you are not teaching the way you used to teach at the start." Claude had gone back to handing over finished headers (Command.h, Editor.h) and asking questions that needed untaught concepts (inheritance).
- **Status report (09-23)** found two contributing settings: the **Learning output style** (on since 09-10) tells Claude to write the routine code and leave the user 2–10-line holes, which conflicts with the blank-file rule. **Ponytail mode** pushes Claude toward terse, answer-first replies. **Both were turned off for `d:	raining` on 09-23** (`.claude/settings.local.json`).

### Where the user struggled
- Mixing up *the buffer* (the text) and *the undo stack* (the history) when shown the whole design at once.
- Polymorphism, inheritance, `virtual`, slicing, and why a stack needs `unique_ptr<Command>`: **given, not learned yet.**
- `const` in `const T&` still gets dropped sometimes.
- Signed vs unsigned: 16 `-Wsign-compare` warnings still sit in old DSA files.

### DSA
- `dsa/day-11/remove-adjacent-duplicates.cpp` (#1047) was created on 09-19. **The user deferred it**: finish the project first.
- **No DSA problem solved since 2026-08-30 (Valid Parentheses).** This breaks the interleave rule.

### English
- Recording #5 is still owed (stack vs queue vs priority_queue, or templates). It was never logged; added to SPEAKING-LOG on 09-23.

### User's own plan (09-20)
> Finish Project 1 → revise all topics → new topics + DSA → Project 2.

## ⏭️ NEXT SESSION agenda (current, 2026-09-23)
Teaching mode: **back to the original rhythm.** One small concept → user predicts → user writes it from a BLANK file → adversarial test → user fixes. No architecture overviews. No dictated headers.
1. **Warm-up (3 questions):** RAII full form + one-liner (failed 09-09); what `const T&` gives you (both halves); why `2 - 10` on `.size()` produces a huge number.
2. **Standalone mini-lesson: inheritance + `virtual`**, outside the project. Tiny example (e.g. `Animal` → `Dog`/`Cat` with `speak()`). Predict-first:
   - what prints *without* `virtual` vs *with* it
   - then slicing (`Animal a = dog;`)
   - then why `vector<unique_ptr<Animal>>` fixes it

   The user writes it from a blank file.
3. **Project 1, Step 4**: the user writes `Editor` themselves (it's the same pattern they just learned).
4. **DSA #1047** (stack pattern, same as Valid Parentheses). The file is ready in `dsa/day-11/`.
5. Then: Steps 5–6 → revision week (CUE boxes; also fix the 16 sign-compare warnings as a revision exercise) → new topics (vector internals, Rule of 0/3/5, iterators) + next DSA pattern → Project 2.
6. Assign English recording #5.

