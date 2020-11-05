project(buf)

if (COVERAGE)
	message(STATUS "Build with coverage-info")
	add_compile_options(-fprofile-arcs -ftest-coverage -O0 -g)
	add_link_options(-fprofile-arcs)
endif()

set(SOURCE_LIB buf.c buf.h)
add_library(buf SHARED ${SOURCE_LIB})
