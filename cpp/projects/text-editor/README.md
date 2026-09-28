# 📝 Project 1 — Text Editor with Undo/Redo

A terminal text editor built to exercise everything from the C++ Mastery track.
This is the **Command Pattern** — the same design Photoshop, Word and every creative
tool uses to implement undo.

## Why this project
Every C++ concept learned so far has a job here:

| Concept | Where it's used |
|---|---|
| Classes, ctor/dtor | `Buffer`, `Command`, `Editor` |
| **RAII** | The editor owns its commands; nothing is manually deleted |
| **`unique_ptr`** | Each command is heap-allocated, single-owner |
| **Polymorphism** | `InsertCommand` / `DeleteCommand` share a `Command` base |
| **`std::move`** | Transferring command ownership between the undo/redo stacks |
| **`stack`** | Two of them — undo and redo |
| **Templates** | Generic helpers (printing, the stacks themselves) |
| **`const` correctness** | Read-only methods and parameters |
| `vector` / `string` | The text buffer itself |

## The core idea (Command Pattern)
Instead of storing *copies of the whole document* after every edit (huge), store
**the actions themselves** — each one knowing how to undo itself.

```
User types "Hello"  →  create InsertCommand("Hello")
                    →  execute() it     (buffer changes)
                    →  push onto undoStack

User hits undo      →  pop from undoStack
                    →  call its undo()  (buffer reverts)
                    →  push onto redoStack
```

Two stacks, and every command can do and undo itself. That's the whole design.

## Build plan (one feature per session)
- [x] **Step 1 — `Buffer`**: a class holding the text, with `insert` / `remove` (clamped) / `getText` / `size` *(done 2026-09-12)*
- [x] **Step 2 — `InsertCommand`**: stores the inserted text; `execute()` / `undo()` *(done 2026-09-19)*
- [x] **Step 3 — `DeleteCommand`**: stores the deleted text so undo can put it back; clamps `count` *(done 2026-09-20)*
- [x] **Step 3½ — split into `include/` + `src/`, `Command` base class** (`virtual`, `= 0`, `override`, virtual destructor). *The base class code was given to me rather than derived, so the inheritance mini-lesson comes before Step 4.*
- [ ] **Step 4 — `Editor` + undo stack**: `unique_ptr` ownership, `std::move` *(`include/Editor.h` exists but is empty)*
- [ ] **Step 5 — Redo stack**: the second stack, and the rule about when it clears
- [ ] **Step 6 — Command loop + `history`**: the interactive terminal front-end
- [ ] **Stretch** — save/load to file (introduces `fstream`, another RAII type)

## Target behaviour
```
> insert Hello world
Buffer: "Hello world"
> insert  again
Buffer: "Hello world again"
> undo
Buffer: "Hello world"
> undo
Buffer: ""
> redo
Buffer: "Hello world"
> delete 5
Buffer: "Hello"
> history
  1. Insert("Hello world")
  2. Delete(5)
> quit
```

## Layout
```
include/   Buffer.h  Command.h  InsertCommand.h  DeleteCommand.h  Editor.h (empty, Step 4)
src/       Buffer.cpp  InsertCommand.cpp  DeleteCommand.cpp  main.cpp
_early/    the original single-file versions of Steps 1-3 (reference only)
```

## Build
```
g++ -Wall -Iinclude src/*.cpp -o editor
./editor
```
Current output: `[Hello] [He] [Hello] []` (insert, delete 3, undo delete, undo insert).
