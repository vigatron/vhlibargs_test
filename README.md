# vhlibargs_test

A minimal C++ test / integration harness for [`vhlibargs`](https://github.com/vigatron/vhlibargs) — a lightweight command-line arguments parser library by [Viktor Glebov](https://github.com/vigatron).

This repository does not implement its own business logic; its purpose is to build `vhlibargs` (and its platform dependency, `vhlibplatform`) as git submodules inside a real executable target, so that the parser can be exercised, linked, and validated outside of its own isolated build tree.

## Overview

| | |
|---|---|
| **Language** | C++17 |
| **Build system** | CMake ≥ 3.22 |
| **Project version** | 0.1.0-rc1 |
| **Primary dependency** | [`vhlibargs`](https://github.com/vigatron/vhlibargs) — command-line arguments parser (v0.1.0-rc1) |
| **Secondary dependency** | [`vhlibplatform`](https://github.com/vigatron/vhlibplatform) — bit manipulation, fixed-width types, runtime diagnostics (v0.4.2) |
| **License** | Not specified at the repository root (see [Notes](#notes-and-open-questions)) |

## Repository Structure

```
vhlibargs_test/
├── .github/workflow/        # CI workflow definition(s)
├── .vscode/                 # Editor/workspace settings
├── src/
│   ├── main.cpp             # Entry point exercising vhlibargs
│   ├── main.hpp
│   └── extmods/
│       ├── vhlibargs/       # git submodule → vigatron/vhlibargs
│       └── vhlibplatform/   # git submodule → vigatron/vhlibplatform
├── tests/                   # Test sources
├── .gitmodules
├── .gitignore
└── CMakeLists.txt
```

## Dependencies

This project pulls in its dependencies as **git submodules** rather than a package manager:

```
[submodule "src/extmods/vhlibplatform"]
    path = src/extmods/vhlibplatform
    url  = https://github.com/vigatron/vhlibplatform

[submodule "src/extmods/vhlibargs"]
    path = src/extmods/vhlibargs
    url  = https://github.com/vigatron/vhlibargs
```

Both are added to the build via `add_subdirectory()` and linked into the main executable as `vhlib_platform` and `vhlib_args`.

## Building

```bash
# Clone with submodules
git clone --recurse-submodules https://github.com/vigatron/vhlibargs_test.git
cd vhlibargs_test

# If already cloned without submodules:
git submodule update --init --recursive

# Configure and build
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

The build produces a single executable target named `vhlibargs_test`, defined from `src/main.cpp` / `src/main.hpp`, linked against `vhlib_platform` and `vhlib_args`. Version macros (`VER_MAJ`, `VER_MIN`, `VER_PAT`) are injected at compile time from the CMake project version.

## Status

This is an early-stage, single-commit test repository (not a polished, documented library on its own). At the time of writing:

- `vhlibargs` itself is still at `v0.1.0-rc1` on its `initial_draft` branch — an unreleased, pre-1.0 API.


