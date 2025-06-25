add_library(cpp_project_template
    calculator.cpp
)

target_include_directories(cpp_project_template
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(main main.cpp)
target_link_libraries(main cpp_project_template)