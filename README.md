# SHA-256 and Cryptographic Prefix Search

## Prerequisites
* CMake 3.14 or higher.
* C compiler supporting C23 standard (GCC or Clang).
* C++ compiler supporting C++14 standard (required for GoogleTest).
* POSIX Threads (pthreads) support.

## Build Instructions

### 1. Generate Build System
Create the build directory and generate the configuration.
```bash
cmake -S . -B build
```

### 2. Compile All Targets
Build the library, executables, and tests simultaneously.
```bash
cmake --build build
```

### 3. Compile Specific Targets (Optional)
Build isolated components using the `--target` flag.

Build the SHA-256 static library:
```bash
cmake --build build --target sha256
```

Build the multithreaded prefix search utility:
```bash
cmake --build build --target prefix_search
```

Build the unit test executable:
```bash
cmake --build build --target test_sha256
```

Build the main placeholder executable:
```bash
cmake --build build --target main
```

## Execution Instructions

### Run the Prefix Search
Execute the binary to initiate the multithreaded brute-force prefix match.
```bash
cmake --build build --target run_prefix_search
```

### Run the Unit Tests
Execute the GoogleTest suite via CTest to verify cryptographic correctness against NIST vectors.
```bash
cmake --build build --target run_tests
```
