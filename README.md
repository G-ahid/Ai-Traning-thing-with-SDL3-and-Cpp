# AI Platformer Training Project

## Overview

This project is an experimental AI training system built alongside a simple SDL3-based 2D platformer environment. The goal is to explore evolutionary-style learning by generating action sequences, evaluating performance, and iteratively improving results through mutation.

The project serves primarily as a learning exercise in C++, SDL3, and basic AI experimentation.

## Concept

Each AI "child" consists of a predefined sequence of actions (e.g., move left, move right, jump). The process works as follows:

1. Generate random action sequences.
2. Simulate the sequence inside the game environment.
3. Evaluate performance using a scoring function.
4. Select and mutate higher-performing sequences.
5. Repeat across generations.

This approach resembles a simplified genetic algorithm where behavior evolves over time based on performance.

## Project Structure

- **Game Engine** – SDL3-based rendering, physics, and collision system.
- **AI Training Module** – Handles generation, evaluation, mutation, and scoring.
- **AI Viewer** – Visualizes saved training results.
- **Build Scripts** – Bash scripts for compiling different components.

## Current Status

- Functional rendering and simulation using SDL3.
- Basic evolutionary training loop implemented.
- Replay and visualization of saved results supported.
- Codebase is experimental and not yet refactored for clarity or scalability.

As this was an early SDL3 project, the structure and architecture are still evolving.

## Planned Improvements

- Refactor and modularize the codebase.
- Improve training stability and scoring reliability.
- Add support for multiple generation persistence.
- Improve replay tooling and debugging utilities.
- Introduce performance optimizations for large simulations.
- Replace custom build scripts with a proper build system (e.g., CMake).

## Requirements

- C++20-compatible compiler (GCC/Clang)
- SDL3 development libraries
- pkg-config
- Bash (for build scripts)

## Building

Use the provided build scripts:

```bash
./compile.sh