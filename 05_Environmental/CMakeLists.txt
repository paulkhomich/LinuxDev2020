cmake_minimum_required(VERSION 3.1)

project(Regexp)
add_executable(Regexp Regexp.c)

find_package(Curses REQUIRED)
find_library(PCRE2_LIBRARY pcre2-8)
if (PCRE2_LIBRARY)
	message(STATUS "pcre2 is found")
endif()
find_path(PCRE2_INCLUDE_DIRS pcre2.h)
find_path(LOCALE_INCLUDE_DIRS locale.h)

include_directories(${CURSES_INCLUDE_DIR} ${PCRE2_INCLUDE_DIRS} ${LOCALE_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(Regexp ${CURSES_LIBRARY} ${PCRE2_LIBRARY})

# --without-UTF
option(WITHOUT_UTF "without-UTF" OFF)

# deep clean
set(GENERATES Makefile CMakeCache.txt CMakeFiles cmake_install.cmake config.h)
add_custom_target(allclean)
add_custom_command(
	TARGET    allclean
	COMMAND   rm -rf ${GENERATES}
)

configure_file(config.h.in config.h)

