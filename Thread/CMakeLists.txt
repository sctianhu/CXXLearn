cmake_minimum_required(VERSION 3.7)

project(CXXThread)
add_compile_options(-std=c++11)
aux_source_directory(. SRC)

add_executable(demo ${SRC})