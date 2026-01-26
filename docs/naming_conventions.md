# C++ Naming Conventions (Rust-Inspired)

This document provides mandatory naming standards for this C++ project, following Rust language conventions.

## Quick Reference (OVERVIEW)

### Most Common Patterns
- **Classes/Structs**: `PascalCase` → `Calculator`, `DataProcessor`
- **Variables**: `snake_case` → `counter`, `file_name`
- **Functions**: `snake_case` → `process_data()`, `get_name()`
- **Members**: `snake_case` → `result`, `is_valid` (NO prefixes)
- **Files**: `snake_case` → `calculator.h`, `data_processor.cpp`
- **Constants**: `SCREAMING_SNAKE_CASE` → `MAX_BUFFER_SIZE`

### File Naming Rules
- **Headers**: `module_name.h` (snake_case)
- **Source**: `module_name.cpp`
- **Tests**: `module_name.test.cpp` or in `tests/`
- **Benchmarks**: `module_name.benchmark.cpp` in `benches/`

## Complete Conventions Table (REFERENCE)

| Element | Convention | Example | Notes |
|---------|------------|---------|-------|
| **Classes** | PascalCase | `DataProcessor`, `HttpClient` | Types (like Rust structs) |
| **Variables** | snake_case | `counter`, `file_name`, `max_retries` | Local & parameters |
| **Class Members** | snake_case | `result`, `is_valid`, `count` | **NO prefixes** (Rust style) |
| **Static Members** | snake_case | `instance_count`, `max_size` | **NO prefixes** (use `static` keyword) |
| **Constants** | SCREAMING_SNAKE_CASE | `MAX_BUFFER_SIZE`, `DEFAULT_TIMEOUT` | Compile-time constants |
| **Global Variables** | snake_case | `application_state`, `is_debug_mode` | **NO prefixes** (avoid globals) |
| **Functions** | snake_case | `process_data()`, `get_name()` | Methods & functions |
| **Function Parameters** | snake_case | `input_file`, `max_retries`, `enable_logging` | No prefixes |
| **Lambda Variables** | snake_case | `process_item`, `filter_data` | Capture variables |
| **Structs** | PascalCase | `Point`, `Configuration` | Like classes |
| **Struct Members** | snake_case | `connection_string`, `port` | **NO prefixes** |
| **Namespaces** | snake_case | `data_processing`, `networking` | Rust-style modules |
| **Enums** | PascalCase | `enum class Color { Red, Green }` | Use enum class |
| **Enum Variants** | PascalCase | `Color::Red`, `Status::Success` | Like Rust enum variants |
| **Templates** | PascalCase | `template<typename T, int Size>` | Type parameters |
| **Type Aliases** | PascalCase | `using StringList = std::vector<std::string>` | **NO _t suffix** (Rust style) |
| **Error Types** | PascalCase + `Error` | `FileNotFoundError`, `ParseError` | Like Rust error types |
| **Traits/Interfaces** | PascalCase | `Drawable`, `Serializable` | **NO I prefix** (Rust style) |
| **Concepts (C++20)** | PascalCase | `Drawable`, `Serializable` | Same as traits |
| **Macros** | SCREAMING_SNAKE_CASE | `MAX_BUFFER_SIZE`, `DEBUG_PRINT` | Use sparingly |
| **Files (Headers)** | snake_case.h | `data_processor.h`, `http_client.h` | Module files |
| **Files (Source)** | snake_case.cpp | `data_processor.cpp`, `http_client.cpp` | Match header |
| **Test Files** | snake_case.test.cpp | `network_manager.test.cpp` | Or in `tests/` directory |
| **Benchmark Files** | snake_case.benchmark.cpp | `network_manager.benchmark.cpp` | In `benches/` directory |
| **Directories** | snake_case | `data_processing/`, `network_utils/` | Lowercase modules |

## Critical Naming Rules (MANDATORY)

### Member Variables (CRITICAL - Rust Style)
```cpp
class Calculator {
private:
    int value;              // NO prefix (Rust style)
    static int count;       // NO prefix, use static keyword
public:
    static const int MAX_VALUE = 100;  // SCREAMING_SNAKE_CASE for constants
};

// Avoid globals, but if needed:
static int application_state;  // NO prefix, use static keyword
```

**Key Principle**: Rely on scope and the `static` keyword instead of name prefixes.

### File Naming Conversion (CRITICAL)
**Rule**: PascalCase class → snake_case file
```cpp
// Class: HttpClient → File: http_client.h/cpp
// Class: DataProcessor → File: data_processor.h/cpp
// Class: XmlParser → File: xml_parser.h/cpp
```

### Error and Trait Naming (CRITICAL - Rust Style)
```cpp
// Error types end with "Error" (not "Exception")
class FileNotFoundError : public std::exception {};
class ParseError : public std::exception {};

// Traits/Interfaces use PascalCase WITHOUT "I" prefix (Rust style)
class Drawable {
public:
    virtual void draw() = 0;
    virtual ~Drawable() = default;
};

class Serializable {
public:
    virtual std::string serialize() = 0;
    virtual ~Serializable() = default;
};
```

## Key Principles (GUIDELINES - Rust-Inspired)

- **Consistency**: Use the same convention throughout the entire project
- **No Hungarian notation**: Avoid encoding type information in names (no `strName`, `nCount`)
- **No prefixes**: Unlike traditional C++, we avoid prefixes (`m_`, `s_`, `g_`, `I`) following Rust conventions
- **Scope-proportional length**: Longer names for broader scope, shorter for narrow scope
- **Readable identifiers**: Names should be self-documenting
- **Use language features**: Use `static`, `const`, access modifiers instead of name prefixes
- **Prefer `const` and `constexpr`**: Use SCREAMING_SNAKE_CASE for constants

## Common Mistakes to Avoid (EXAMPLES)

```cpp
// BAD - Using prefixes (old C++ style)
class Calculator {
    int m_value;          // Should be: int value;
    static int s_count;   // Should be: static int count;
};
int g_global;            // Should be: static int global; (or avoid globals)

// BAD - Wrong case
void ProcessData();      // Should be process_data()
class dataProcessor;     // Should be DataProcessor
namespace DataProcessing; // Should be data_processing

// BAD - Hungarian notation
int nCounter;            // Should be counter
std::string strName;     // Should be name

// BAD - Old naming patterns
class IDrawable { };     // Should be: class Drawable { };
class IOException { };   // Should be: class IoError { };
using String_t = std::string;  // Should be: using String = std::string;

// GOOD - Correct Rust-style naming
class DataProcessor {
private:
    int value;                    // Clean field names
    static int instance_count;    // No s_ prefix
public:
    static const int MAX_SIZE = 1000;  // SCREAMING_SNAKE_CASE
    void process_data();          // snake_case methods
};

// GOOD - Namespaces as modules
namespace data_processing {      // snake_case
    class Parser { };            // PascalCase type
    void parse_file();           // snake_case function
}
```

## Quick Lookup by Type (REFERENCE)

### Variables (QUICK REFERENCE - Rust Style)
- Local: `snake_case`
- Member: `snake_case` (NO prefix)
- Static: `snake_case` (NO prefix, use `static` keyword)
- Constant: `SCREAMING_SNAKE_CASE`
- Global: `snake_case` (avoid, use `static` at namespace scope)

### Types (QUICK REFERENCE - Rust Style)
- Class/Struct/Union: `PascalCase`
- Trait/Interface: `PascalCase` (NO "I" prefix)
- Error: `PascalCaseError` (not "Exception")
- Enum: `PascalCase`
- Enum Variant: `PascalCase`
- Type Alias: `PascalCase` (NO "_t" suffix)

### Files (QUICK REFERENCE)
- Header: `snake_case.h`
- Source: `snake_case.cpp`
- Test: `snake_case.test.cpp` (or in `tests/`)
- Benchmark: `snake_case.benchmark.cpp` (in `benches/`)

### Namespaces (QUICK REFERENCE - Rust Style)
- Namespace: `snake_case` (like Rust modules)

---

Following these Rust-inspired naming conventions ensures code consistency, maintainability, and readability across the entire project while maintaining C++ compatibility.