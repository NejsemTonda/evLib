cmake_minimum_required(VERSION 3.19)

project("krnakva")

add_executable("test")
set_property(TARGET "test" PROPERTY CXX_STANDARD 20)
target_sources("test" PUBLIC "main.cpp")

add_subdirectory("examples")
