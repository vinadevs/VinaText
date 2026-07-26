# CLAUDE.md

VinaText is mid-migration from Windows-only MFC to cross-platform **Qt**
(Windows + macOS + Linux).

**Read `doc/QT-PORT-BRIEF.md` before proposing any architectural change, adding any
dependency, or touching `src/stdafx.h`.** It records what has already been measured and
decided — including several decisions that are settled and should not be re-argued.

**Read `doc/PORTING.md` before moving, rewriting, or deleting any file in `src/`.** It
classifies all 137 `src/*.cpp` into core / platform / ui-rewrite / delete, with `CString`
counts, and sets the Phase 2 work order.

## Hard rules

- **VinaText is MIT. Never add a GPL dependency.**
  - Never use **QScintilla** (GPL-or-commercial). Use upstream Scintilla's
    `qt/ScintillaEditBase` instead.
  - Never link Qt **statically** — LGPLv3 compliance depends on dynamic linking.
  - Avoid GPL-only Qt modules (list in the brief, §4 D3).
- **The MFC build must keep building and shipping to Windows users.** Do not break it.
- **New Qt code goes in `ui-qt/`**, gated behind the `VINATEXT_BUILD_QT` CMake option
  (default OFF).
- Work happens **directly in this repo — no fork.** All port work targets the long-lived
  **`port/cross-platform`** branch; PRs point at it, never at `master`. `master` is for
  shipping MFC releases (`release_1.x`) until Phase 6 cutover. (Brief §4 D4.)
- **Do not rewrite git history** to shrink the repo — forks exist and it breaks clones.

## Orientation

- `src/*.cpp` = **137 files**, VinaText's own code, ~101k LOC. This is what gets ported.
- `find src -name '*.cpp'` = 193 — includes vendored `uchardet`, `tinyXml`, `pdf/UXReader`.
  **Do not rewrite vendored code.** Use the `src/*.cpp` glob.
- `src/stdafx.h` is a god-header pulling all of MFC/ATL/Win32/GDI+/Boost into **all 137**
  `.cpp`. Breaking it gates every other phase. (Four files spell it `StdAfx.h`; a
  case-sensitive grep undercounts to 133. Use `grep -il`.)
- Code style: see `doc/code_convention.txt` (C++11+, `MyClass`/`MyMethod` upper camel,
  `m_` members, Allman braces). Match it; don't switch to Qt's own conventions.
