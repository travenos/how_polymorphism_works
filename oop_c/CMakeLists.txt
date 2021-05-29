cmake_minimum_required(VERSION 2.8)

project(oop_c)
add_executable(${PROJECT_NAME} "main.c")
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
