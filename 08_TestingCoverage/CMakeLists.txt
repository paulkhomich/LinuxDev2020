cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(buf_testing)
set(SOURCE_EXE main.c)

include_directories(src)
add_subdirectory(src)
add_executable(main ${SOURCE_EXE})

# Tests
enable_testing()
add_subdirectory(tests)

target_link_libraries(main buf)

# Coverage
add_custom_target(gcov)
add_custom_command(TARGET gcov
	COMMAND echo "====== GCOV ======"
	COMMAND mkdir -p Coverage
	COMMAND find ./ -name "*.gcno" -exec gcov {} "\;"
	COMMAND mv *.gcov ./Coverage
	COMMAND echo ".gcov files in ./Coverage"
)
