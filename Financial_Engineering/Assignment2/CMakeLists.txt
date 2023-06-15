cmake_minimum_required(
    VERSION 3.10 FATAL_ERROR
)

project(order_manager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -pedantic -Werror)

# order manager based on sort
# TODO
set(order_manager_v1_files main.cpp order.cpp order_manager_v1.cpp)

add_executable(order_manager_v1 ${order_manager_v1_files})

# order manager based on lower/upper bound
# TODO
set(order_manager_v2_files main.cpp order.cpp order_manager_v2.cpp)

add_executable(order_manager_v2 ${order_manager_v2_files})