# C++ Code Guidelines

This document outlines the code formatting and inclusion standards for this project.

## Code Formatting

The project uses `clang-format` with Microsoft style as the base configuration. The specific formatting rules are defined in `.clang-format`:

- **Base Style**: Microsoft
- **Short Functions**: Allowed on a single line
- **Pointer Alignment**: Left-aligned (`int* ptr` not `int *ptr`)
- **Pointer Alignment Derivation**: Disabled (consistent left alignment)

Run `clang-format` on all source files before committing:
```bash
clang-format -i src/**/*.{cpp,h} include/**/*.h tests/**/*.cpp
```

## Header Inclusion Rules

### Inclusion Policy
- **No implicit inclusion**: All dependencies must be explicitly included
- **No transitive dependencies**: Do not rely on headers included by other headers
- **Forward declarations**: Use forward declarations whenever possible to reduce compilation dependencies

### Header Sorting Order

Headers must be grouped and sorted in the following order:

1. **Precompiled Headers** (if existing)
   ```cpp
   #include "pch.h"
   ```

2. **First-party Headers** (project headers)
   ```cpp
   #include "calculator.h"
   #include "data_processor.h"
   ```

3. **Third-party Headers** (external libraries)
   ```cpp
   // Group by library/project when relevant
   #include <gtest/gtest.h>
   #include <gmock/gmock.h>
   #include <benchmark/benchmark.h>
   ```

4. **Standard Library Headers**
   ```cpp
   #include <algorithm>
   #include <memory>
   #include <string>
   #include <vector>
   ```

### Sorting Within Groups
- Sort alphabetically within each group
- Use blank lines to separate groups
- Third-party headers may be sub-grouped by library/framework if it improves readability

### Example Header Organization
```cpp
// Precompiled header (if used)
#include "pch.h"

// First-party headers
#include "calculator.h"
#include "math_utils.h"

// Third-party headers
#include <gtest/gtest.h>
#include <benchmark/benchmark.h>

// Standard library headers
#include <iostream>
#include <memory>
#include <vector>
```

## Rationale

This header organization ensures:
- **Dependency clarity**: All dependencies are explicit and visible
- **Build reliability**: No hidden dependencies through transitive inclusion
- **Maintainability**: Easy to identify what each file depends on
- **Compilation speed**: Precompiled headers first, followed by logical dependency order