cmake_minimum_required(VERSION 3.0)
project(guess VERSION 0.0)
add_subdirectory(locale)
add_subdirectory(docs)

add_executable(guess main.c)

find_package(Intl REQUIRED)
include_directories(${Intl_INCLUDE_DIR})
target_link_libraries(guess ${Intl_LIBRARY})

find_package(Gettext REQUIRED)
