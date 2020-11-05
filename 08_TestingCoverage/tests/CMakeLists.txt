find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIR})

add_executable(basic basic.c)
add_test(NAME basic COMMAND basic)

add_executable(buffer buffer.c)
target_link_libraries(buffer ${CHECK_LIBRARIES} buf)
add_test(NAME buffer COMMAND buffer)
