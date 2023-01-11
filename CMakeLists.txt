cmake_minimum_required(VERSION 3.22.1)

project(static_deque)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/coverage)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/coverage/report)

add_compile_options(-Wall -Wextra -Werror -Wconversion --coverage -fdiagnostics-color=always)
add_link_options(--coverage)

add_executable(Test_Exec test/test.cpp test/unity/unity.c)

add_custom_target(
  Test_Run
  COMMAND Test_Exec
  DEPENDS Test_Exec
)

add_custom_target(Test_Eval ALL
    COMMAND gcovr -s --exclude-throw-branches --decision -r ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/CMakeFiles/Test_Exec.dir/test
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR}/src --exclude-throw-branches --decision --json-summary-pretty --html --html-details --output report/ ${CMAKE_BINARY_DIR}/CMakeFiles/Test_Exec.dir/test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
    DEPENDS Test_Run
)
