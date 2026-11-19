# vhlibargs_test

Revision: 0.1.2

A minimal C++ test / integration harness for [`vhlibargs`](https://github.com/vigatron/vhlibargs) — a lightweight command-line arguments parser library by [Viktor Glebov](https://github.com/vigatron).

This repository does not implement its own business logic; its purpose is to build `vhlibargs` (and its platform dependency, `vhlibplatform`) as git submodules inside a real executable target, so that the parser can be exercised, linked, and validated outside of its own isolated build tree.

## Overview

| | |
|---|---|
| **Language** | C++17 |
| **Build system** | CMake ≥ 3.16 |
| **Primary dependency** | [`vhlibargs`](https://github.com/vigatron/vhlibargs) — command-line arguments parser (v0.2.1) |
| **Secondary dependency** | [`vhlibplatform`](https://github.com/vigatron/vhlibplatform) — bit manipulation, fixed-width types, runtime diagnostics (v0.4.2) |
| **License** | Not specified at the repository root (the dependencies `vhlibargs` and `vhlibplatform` are MIT-licensed) |

## Repository Structure

```
vhlibargs_test/
├── .github/workflows/       # CI workflow definition(s)
├── .vscode/                 # Editor/workspace settings
├── src/
│   ├── main.cpp             # Entry point exercising vhlibargs
│   ├── main.hpp
│   └── extmods/
│       ├── vhlibargs/       # git submodule → vigatron/vhlibargs
│       └── vhlibplatform/   # git submodule → vigatron/vhlibplatform
├── tests/                   # Python integration test harness (runtests.py)
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

## Running tests

```bash
python3 tests/runtests.py
```

The harness invokes the already-built `vhlibargs_test` (from `build/`, so build it first), checks exit codes against expected results, and exits non-zero on the first failing case. Prints `All tests passed` on success. The same steps run in CI (`.github/workflows/ci.yml`) on pull requests to `main`.

## Status

A test/integration harness for `vhlibargs` (not a polished, documented library on its own). The `vhlibargs` submodule is currently checked out at `rev0.2.1`; the harness is continuously built and tested in CI.

