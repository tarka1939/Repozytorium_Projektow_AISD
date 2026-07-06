# Repozytorium Projektów AISD

A collection of C++ programming assignments completed for **AISD (Algorytmy i Struktury Danych — "Algorithms and Data Structures")**, a core computer science university course. Each folder is an independent Visual Studio solution solving a distinct, graded algorithmic problem, almost entirely with hand-written data structures rather than the C++ Standard Library.

## Projects

### [Proj_AISD_1_2024](Proj_AISD_1_2024) — RPN Expression Calculator
Parses infix arithmetic expressions, converts them to postfix (Reverse Polish Notation) using the shunting-yard algorithm, and evaluates them. Supports standard operators plus `min`, `max`, `if`, and unary negation. Built on custom `Stack`, `Queue`, `Vector`, and `myString` containers ([RPN.h](Proj_AISD_1_2024/Proj_AISD_1_2024/RPN.h)) implemented from scratch.

### [AISD_Proj2_2024 Hex](AISD_Proj2_2024%20Hex) — Hex Board Game Engine
Parses a serialized Hex board, validates whether the board state is legal/reachable, detects whether the game is over, and determines whether a given player can force a win within *N* moves. Implements board-connectivity search and win detection using custom containers instead of STL equivalents ([game.h](AISD_Proj2_2024%20Hex/AISD_Proj2_2024%20Hex/game.h)).

### [AISD_Proj3](AISD_Proj3) — Graph & Tree Algorithms Toolkit
A suite of classic graph analyses run over both adjacency-matrix and adjacency-list representations ([GraphMatrix.cpp](AISD_Proj3/AISD_Proj3/GraphMatrix.cpp), [GraphList.cpp](AISD_Proj3/AISD_Proj3/GraphList.cpp)):
- degree sequence, connected components, bipartiteness testing, vertex eccentricity
- three greedy vertex-coloring heuristics (Greedy, Largest-First, Saturation-Largest-First)
- C4-subgraph counting and complement-graph edge counting

Also includes a self-balancing **AVL binary search tree** with duplicate-key counting ([tree.h](AISD_Proj3/AISD_Proj3/tree.h)).

### [ProjektAIDS2](ProjektAIDS2) — CSS Block Parser
A hand-rolled parser for a CSS-like stylesheet syntax. Reads selector/attribute/value blocks from stdin into custom `List`/`BlockList` structures ([Css.h](ProjektAIDS2/ProjektAIDS2/Css.h)) and answers queries against the parsed style rules — essentially a miniature style-resolution engine built without any parsing libraries.

### [C++_ProjectAIDS_2_JakDojade_Graph_Dijkstra](C++_ProjectAIDS_2_JakDojade_Graph_Dijkstra) — "JakDojade" Route Planner
Builds a weighted graph from an ASCII city map (stations marked as cells), discovers connectivity via flood fill, and answers shortest-route queries between named stops using **Dijkstra's algorithm** with a custom hash map ([Graph.h](C%2B%2B_ProjectAIDS_2_JakDojade_Graph_Dijkstra/C%2B%2B_ProjectAIDS_2_JakDojade_Graph_Dijkstra/Graph.h), [HashMap.h](C%2B%2B_ProjectAIDS_2_JakDojade_Graph_Dijkstra/C%2B%2B_ProjectAIDS_2_JakDojade_Graph_Dijkstra/HashMap.h)). The name and problem framing are modeled on [jakdojade.pl](https://jakdojade.pl), a Polish public-transport journey-planning service.

## Purpose

These are individually graded university coursework projects, each solved against a fixed set of input/output test cases (bundled per-project as `*.in`/`*.out` files) with correctness and performance requirements enforced by an autograder.

## Why it matters beyond the classroom

Although academic in origin, the repository demonstrates engineering skills directly transferable to professional software work:

- **Data structures from first principles** — stacks, queues, vectors, strings, linked lists, hash maps, and AVL trees are all implemented manually, showing a working understanding of memory management, pointers, and complexity trade-offs rather than just calling into `<vector>`/`<map>`.
- **Algorithmic breadth** — shunting-yard parsing, graph traversal and shortest paths, greedy heuristics, tree self-balancing, and recursive-descent-style text parsing are all represented.
- **Performance awareness** — several solutions carry inline notes about time-limit and memory-limit constraints (e.g. optimizing a solution that initially exceeded a time limit or consumed excessive RAM), reflecting the same profiling/optimization mindset needed in production systems.
- **Test-driven verification** — every project ships with numbered test fixtures and expected outputs, mirroring the discipline of validating logic against known cases before shipping.
- **Real-world-inspired modeling** — the Dijkstra project reframes a graph/shortest-path problem as a transit route planner, and the CSS project reframes a parsing problem as a stylesheet engine, showing the ability to map textbook algorithms onto realistic product scenarios.

## Building

Each project is a standalone **Visual Studio solution** (`.sln` + `.vcxproj`) targeting the **v143 (Visual Studio 2022) MSVC toolset** on Windows, built for the `x64` platform. Open the relevant `.sln` file in Visual Studio and build/run directly, or run the compiled binary with the provided `*.in` test file piped to stdin, e.g.:

```powershell
.\AISD_Proj3.exe < test_10_in.txt
```

Expected output for each test case is provided in the matching `*_out.txt` / `*.out` file for comparison.
