# C++ Naming Conventions

Please follow these naming conventions consistently throughout the codebase:

| Element | Convention | Example |
|---------|------------|---------|
| Classes | PascalCase | `DataProcessor`, `HTTPClient` |
| Variables | camelCase | `counter`, `fileName`, `maxRetries` |
| Class Members | camelCase with `m_` prefix | `m_result`, `m_isValid` |
| Static Members | camelCase with `s_` prefix | `s_instanceCount`, `s_maxSize` |
| Global Variables | camelCase with `g_` prefix | `g_applicationState`, `g_isDebugMode` |
| Functions | camelCase | `processData()`, `getName()` |
| Function Parameters | camelCase | `inputFile`, `maxRetries`, `enableLogging` |
| Lambda Variables | camelCase | `processItem`, `filterData` |
| Structs | PascalCase | `Point`, `Configuration` |
| Struct Members | camelCase (no prefix) | `connectionString`, `port` |
| Unions | PascalCase | `DataValue`, `MessageContent` |
| Namespaces | PascalCase | `DataProcessing`, `Networking` |
| Enums | PascalCase | `enum class Colour { Red, Green }` |
| Templates | PascalCase | `template<typename T, int Size>` |
| Type Aliases | PascalCase | `using StringList = std::vector<std::string>` |
| Exception Classes | PascalCase with Exception suffix | `FileNotFoundException`, `InvalidArgumentException` |
| Interface Classes | PascalCase with I prefix | `IDrawable`, `ISerializable` |
| Concepts (C++20) | PascalCase | `Drawable`, `Serializable` |
| Macros | UPPERCASE | `MAX_BUFFER_SIZE`, `DEBUG_PRINT` |
| Files | snake_case | `data_processor.h`, `http_client.cpp` |
| Benchmarks | original_name.benchmark.cpp | `network_manager.benchmark.cpp` |
| Tests | original_name.test.cpp | `network_manager.test.cpp` |
| Directories | snake_case | `data_processing/`, `network_utils/` |

## Key Points

- Use consistent naming throughout the project
- Avoid encoding type information in names
- Make name length proportional to scope (longer names for broader scope)
- File names use snake_case with conversion from PascalCase class names (e.g., `HTTPClient` → `http_client.h`)