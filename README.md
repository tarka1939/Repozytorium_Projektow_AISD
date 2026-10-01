# Algorithms & Data Structures in C++

[![CI](https://github.com/tarka1939/Repozytorium_Projektow_AISD/actions/workflows/ci.yml/badge.svg)](https://github.com/tarka1939/Repozytorium_Projektow_AISD/actions/workflows/ci.yml)

Five graded assignments from the university course *Algorytmy i Struktury Danych* (Algorithms and Data Structures). Each one is a console program that reads a problem from stdin and is checked against fixed input/output files. The rule for the course was to write the data structures yourself, so the stacks, queues, vectors, strings, linked lists, block lists, AVL tree and binary heap here are hand-written (exceptions are listed under [Limitations](#limitations)).

All five build with CMake on Linux (GCC) and Windows (MSVC). The original Visual Studio solutions still work. CI runs every test suite on both platforms.

## Results

| Project | What it does | Techniques | Verified by the test runner |
|---|---|---|---|
| **RPN calculator**<br>[`Proj_AISD_1_2024`](Proj_AISD_1_2024) | Converts infix formulas to postfix and evaluates them step by step: `+ − * /`, unary `N`, `IF(a,b,c)`, `MIN`/`MAX` with any number of arguments, division-by-zero detection | Shunting-yard with per-parenthesis argument counting; hand-written `Stack`, `Queue`, `Vector`, `myString` | Fixtures, plus **300 random nested expressions** checked against an independent recursive-descent evaluator |
| **CSS query engine**<br>[`ProjektAIDS2`](ProjektAIDS2) | Parses stylesheet sections, answers queries (counts, selector/attribute lookup, value of an attribute for a selector) and handles deletions | Block list (unrolled linked list of fixed-size blocks) over a hand-written doubly linked list | Example in the assignment's format, checked by hand against the command spec |
| **Hex engine**<br>[`AISD_Proj2_2024 Hex`](AISD_Proj2_2024%20Hex) | Parses an ASCII Hex board and answers: board size, pawn count, is the board legal, is the game over, could the position have been reached, can a player win in 1 or 2 moves against a naive opponent | Iterative DFS over the hex grid with an explicit stack; own `Vector`/`List`/`myString`; no STL containers | **10 grader files, 9,900 answers, all match**, slowest file 0.4 s |
| **Graph toolkit**<br>[`AISD_Proj3`](AISD_Proj3) | For each input graph: degree sequence, number of components, bipartiteness, vertex eccentricities, three greedy colourings (greedy, Largest-First, Saturation-LF), number of C4 subgraphs, number of edges in the complement | Adjacency lists, BFS, AVL tree for sorting, DFS-based 4-cycle counting | **4 grader files: all 9 implemented queries match.** C4 counting also checked on 200 random graphs against an independent formula |
| **JakDojade route planner**<br>[`C++_ProjectAIDS_2_JakDojade_Graph_Dijkstra`](C++_ProjectAIDS_2_JakDojade_Graph_Dijkstra) | Builds a weighted graph from an ASCII map (cities `*`, roads `#`, names next to cities) plus one-way flights, then answers shortest-route queries with the cities on the way | BFS flood fill from each city; Dijkstra with a hand-written binary heap | **13 of 14 grader tests match**, plus a regression test. The 100,000-city tests take about 0.4 s; the 42 MB input about 3 s. One reference output is disputed (see below) |

Run it yourself:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
python tests/run_tests.py build
```

Each program can also be run on its own, e.g. `./build/hex < "AISD_Proj2_2024 Hex/AISD_Proj2_2024 Hex/16.in.txt"`. On Windows, open any `.sln` in Visual Studio 2022 and build it.

## Bugs found and fixed after grading

The graded submissions are in the git history. Making the projects build on Linux and adding the test runner exposed several bugs that were then fixed. The commit messages have the details:

| Project | Problem | Fix | Effect |
|---|---|---|---|
| JakDojade | Dijkstra scanned all cities for the next one to visit, O(V²) per query | Hand-written binary min-heap ordered by (cost, id), so tie-breaking and printed routes are unchanged | 100,000-city tests: **11.3 s → 0.5 s** (these two tests exceeded the grader's time limit) |
| JakDojade | Cities were keyed by a 32-bit hash of their name with no collision check, so colliding names were merged | Key by the full name | `ABKJV`/`NAAAA` collide: answers were 4/4/0, now 10/4/6 ([`tests/hash_collision.in`](C++_ProjectAIDS_2_JakDojade_Graph_Dijkstra/tests)) |
| JakDojade | Map rows were read into a buffer one byte too small; with CRLF input every read failed on Linux | Correct buffer size, strip `\r` | Reads LF and CRLF input; identical test results on Linux and Windows in CI |
| Graph toolkit | The C4 counter held a reference into its DFS stack and overwrote it on the next push | Copy the entry | C4 answers went from mostly wrong (e.g. 17 instead of 473) to all correct |
| RPN calculator | `MIN`/`MAX` were parsed but never evaluated | Count arguments while converting; emit `MINn`/`MAXn` | Random-expression check: 341/500 → 500/500 |
| CSS engine | Never exited at end of input; read past the end of the list for missing sections | Handle EOF; check indices | Terminates; no AddressSanitizer/UBSan reports on the sample input |
| All | Only compiled with MSVC (wrong-case includes, missing standard headers, `<windows.h>`) | Standard C++17 headers | Builds with GCC and MSVC in CI |

## Limitations

- **Planarity** (query 5 in the graph toolkit) is not implemented; the program answers `?`, which the assignment allows. The test runner skips that line.
- **Hex:** the "win in N moves" queries cover N = 1 and 2 against a *naive* opponent, as in the assignment; there is no perfect-opponent search.
- **JakDojade test 2:** the reference output gives 23 for the first query. An independent BFS over the map gives 22, the same as this program, so the test is reported as a known deviation rather than a failure.
- **Standard library:** the JakDojade city index uses `std::unordered_map`/`std::string`; everything else uses the hand-written containers. Those containers have no copy constructors or freeing destructors (copies share storage, memory is released at exit), which is enough for these batch programs but not production-grade.

## Layout

| Folder | Project |
|---|---|
| `Proj_AISD_1_2024/` | RPN calculator (+ `tests/`) |
| `ProjektAIDS2/` | CSS query engine (+ `tests/`) |
| `AISD_Proj2_2024 Hex/` | Hex engine (fixtures `N.in.txt` / `N.out.txt` next to the sources) |
| `AISD_Proj3/` | Graph toolkit (fixtures `test_*_in.txt` / `test_*_out.txt`) |
| `C++_ProjectAIDS_2_JakDojade_Graph_Dijkstra/` | JakDojade route planner (+ `tests/`, grader tests in `grader_tests.tar.xz`) |
| `tests/run_tests.py` | Runs every suite; `CMakeLists.txt` builds every program |
