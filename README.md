# Uebrsat - SAT Solver / Model Counter in Rust

## Overview

Uebrsat is a fast and efficient SAT (Boolean Satisfiability Problem) solver implemented in Rust. It uses modern algorithms and data structures to determine the satisfiability of propositional logic formulas expressed in Conjunctive Normal Form (CNF). Designed with performance and extensibility in mind, Uebrsat aims to provide a reliable tool for both academic research and practical industrial applications.

## Key Features

- **Efficient Unit Propagation:** Implements optimized unit clause propagation to prune the search space quickly.
- **Conflict-Driven Clause Learning (CDCL):** Learns from conflicts to avoid repeating the same mistakes.
- **Backtracking and Decision Heuristics:** Uses heuristics to decide variable assignments intelligently.
- **Incremental Solving:** Supports solving related problems incrementally without restarting from scratch.
- **Rust-based:** Leverages Rust's safety, concurrency, and performance advantages.

## Industrial Applications

SAT solvers like Uebrsat play a critical role in many industries by enabling automated reasoning and decision-making:

- **Hardware and Software Verification:** Ensuring circuits and programs behave correctly by encoding properties as SAT problems.
- **Automated Planning and Scheduling:** Solving complex planning tasks in logistics, manufacturing, and AI.
- **Model Checking:** Verifying system properties in safety-critical domains like aerospace and automotive.
- **Cryptanalysis:** Breaking cryptographic schemes by modeling attacks as SAT problems.
- **Optimization Problems:** Encoding combinatorial optimization problems for efficient solution search.

By providing a robust SAT solver in Rust, Uebrsat helps engineers and researchers efficiently tackle these complex problems with high reliability and performance.

## Getting Started



---

*Developed by Ishan Kumthekar*
