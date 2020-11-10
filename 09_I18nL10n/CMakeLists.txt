cmake_minimum_required(VERSION 2.8)
project(guess)
add_subdirectory(locale)

add_executable(guess main.c)

find_package(Intl REQUIRED)
include_directories(${Intl_INCLUDE_DIR})
target_link_libraries(guess ${Intl_LIBRARY})

find_package(Gettext REQUIRED)
