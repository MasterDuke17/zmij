cmake_minimum_required(VERSION 3.16)
project(zmij CXX)

set(ZMIJ_STANDARD cxx_std_17)

add_library(zmij zmij.cc zmij.h)
target_compile_features(zmij PRIVATE ${ZMIJ_STANDARD})

add_executable(example example.cc)
target_link_libraries(example zmij)

set(CMAKE_CTEST_ARGUMENTS "--output-on-failure")
enable_testing()
add_subdirectory(gtest)

add_executable(zmij-test zmij-test.cc)
target_compile_features(zmij-test PRIVATE ${ZMIJ_STANDARD})
target_link_libraries(zmij-test gtest)
add_test(NAME zmij-test COMMAND zmij-test)

add_executable(zmij-no-int128-test zmij-test.cc)
target_compile_features(zmij-no-int128-test PRIVATE ${ZMIJ_STANDARD})
target_compile_definitions(zmij-no-int128-test PRIVATE ZMIJ_USE_INT128=0)
target_link_libraries(zmij-no-int128-test gtest)
add_test(NAME zmij-no-int128-test COMMAND zmij-no-int128-test)
