# C++ Naming Conventions

This document provides mandatory naming standards when working with this C++ project.

## Quick Reference

### Most Common Patterns
- **Classes**: `PascalCase` → `Calculator`, `DataProcessor`
- **Variables**: `snake_case` → `counter`, `file_name`
- **Functions**: `snake_case` → `process_data()`, `get_name()`
- **Members**: `m_snake_case` → `m_result`, `m_is_valid`
- **Files**: `snake_case` → `calculator.h`, `data_processor.cpp`
- **Macros**: `UPPERCASE` → `MAX_BUFFER_SIZE`

### File Naming Rules
- **Headers**: `class_name.h` (PascalCase → snake_case)
- **Source**: `class_name.cpp`
- **Tests**: `class_name.test.cpp`
- **Benchmarks**: `class_name.benchmark.cpp`

## Complete Conventions Table

| Element | Convention | Example | Notes |
|---------|------------|---------|-------|
| **Classes** | PascalCase | `DataProcessor`, `HTTPClient` | Main types |
| **Variables** | snake_case | `counter`, `file_name`, `max_retries` | Local & parameters |
| **Class Members** | `m_` + snake_case` | `m_result`, `m_is_valid` | **MANDATORY m_ prefix** |
| **Static Members** | `s_` + snake_case` | `s_instance_count`, `s_max_size` | **MANDATORY s_ prefix** |
| **Global Variables** | `g_` + snake_case` | `g_application_state`, `g_is_debug_mode` | **MANDATORY g_ prefix** |
| **Functions** | snake_case | `process_data()`, `get_name()` | Methods & functions |
| **Function Parameters** | snake_case | `input_file`, `max_retries`, `enable_logging` | No prefixes |
| **Lambda Variables** | snake_case | `process_item`, `filter_data` | Capture variables |
| **Structs** | PascalCase | `Point`, `Configuration` | Like classes |
| **Struct Members** | snake_case | `connection_string`, `port` | **NO prefixes** |
| **Namespaces** | PascalCase | `DataProcessing`, `Networking` | Module names |
| **Enums** | PascalCase | `enum class Colour { red, green }` | Use enum class |
| **Templates** | PascalCase | `template<typename T, int Size>` | Type parameters |
| **Type Aliases** | PascalCase + `_t` | `using StringList_t = std::vector<std::string>` | **MANDATORY _t suffix** |
| **Exception Classes** | PascalCase + Exception | `FileNotFoundException`, `InvalidArgumentException` | **MANDATORY suffix** |
| **Interface Classes** | I + PascalCase | `IDrawable`, `ISerializable` | **MANDATORY I prefix** |
| **Concepts (C++20)** | PascalCase | `Drawable`, `Serializable` | No I prefix |
| **Macros** | UPPERCASE | `MAX_BUFFER_SIZE`, `DEBUG_PRINT` | Use sparingly |
| **Files (Headers)** | snake_case.h | `data_processor.h`, `http_client.h` | **Class → file conversion** |
| **Files (Source)** | snake_case.cpp | `data_processor.cpp`, `http_client.cpp` | Match header |
| **Test Files** | snake_case.test.cpp | `network_manager.test.cpp` | **MANDATORY .test.cpp** |
| **Benchmark Files** | snake_case.benchmark.cpp | `network_manager.benchmark.cpp` | **MANDATORY .benchmark.cpp** |
| **Directories** | snake_case | `data_processing/`, `network_utils/` | Lowercase |

## Critical Naming Rules

### Member Variable Prefixes (MANDATORY)
```cpp
class Calculator {
private:
    int m_value;        // REQUIRED m_ prefix
    static int s_count; // REQUIRED s_ prefix
};

int g_global_counter;    // REQUIRED g_ prefix with snake_case
```

### File Naming Conversion (MANDATORY)
**Rule**: PascalCase class → snake_case file
```cpp
// Class: HTTPClient → File: http_client.h/cpp
// Class: DataProcessor → File: data_processor.h/cpp
// Class: XMLParser → File: xml_parser.h/cpp
```

### Exception and Interface Naming (MANDATORY)
```cpp
// Exceptions MUST end with "Exception"
class FileNotFoundException : public std::exception {};
class InvalidArgumentException : public std::exception {};

// Interfaces MUST start with "I"
class IDrawable {
public:
    virtual void draw() = 0;
};
```

## Key Principles (MANDATORY)

- **Consistency**: Use the same convention throughout the entire project
- **No Hungarian notation**: Avoid encoding type information in names (no `strName`, `nCount`)
- **Scope-proportional length**: Longer names for broader scope, shorter for narrow scope
- **Readable identifiers**: Names should be self-documenting
- **Prefix adherence**: Always use required prefixes (m_, s_, g_, I)

## Common Mistakes to Avoid

```cpp
// BAD - Missing prefixes
class Calculator {
    int value;          // Should be m_value
    static int count;   // Should be s_count
};

// BAD - Wrong case
void ProcessData();     // Should be process_data()
class dataProcessor;    // Should be DataProcessor

// BAD - Hungarian notation
int nCounter;           // Should be counter
std::string strName;    // Should be name

// GOOD - Correct naming
class DataProcessor {
private:
    int m_value;
    static int s_instance_count;
public:
    void process_data();
};
```

## Quick Lookup by Type

### Variables
- Local: `snake_case`
- Member: `m_snake_case`
- Static: `s_snake_case`
- Global: `g_snake_case`

### Types
- Class/Struct/Union: `PascalCase`
- Interface: `IPascalCase`
- Exception: `PascalCaseException`
- Enum: `PascalCase`

### Files
- Header: `snake_case.h`
- Source: `snake_case.cpp`
- Test: `snake_case.test.cpp`
- Benchmark: `snake_case.benchmark.cpp`