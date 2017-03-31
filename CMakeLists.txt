cmake_minimum_required(VERSION 3.6)
project(byl_template_library)

set(CMAKE_CXX_STANDARD 11)
#add_subdirectory(test)
aux_source_directory(src/ SOURCE_FILES)
add_library(byl_template_library ${SOURCE_FILES} src/byl_kmp.h test/kmp_test.cpp)