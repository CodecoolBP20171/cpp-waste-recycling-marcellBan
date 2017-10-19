cmake_minimum_required(VERSION 2.8.2)
project(recycling)
set(CMAKE_CXX_STANDARD 11)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif ()


# google test unit tests
set(TEST_SOURCES src/garbage/Garbage.cpp include/garbage/Garbage.h tests/DustbinTests.cpp src/garbage/PaperGarbage.cpp include/garbage/PaperGarbage.h src/garbage/PlasticGarbage.cpp include/garbage/PlasticGarbage.h include/dustbin/DustbinErrors.hpp src/dustbin/Dustbin.cpp include/dustbin/Dustbin.h src/dustbin/Dustbin9k.cpp include/dustbin/Dustbin9k.h src/garbage/MetalGarbage.cpp include/garbage/MetalGarbage.h src/garbage/BottleCap.cpp include/garbage/BottleCap.h)
add_executable(DustbinTest ${TEST_SOURCES})
target_link_libraries(DustbinTest gtest_main)

# release build
set(RELEASE_SOURCES src/garbage/Garbage.cpp include/garbage/Garbage.h src/garbage/PaperGarbage.cpp include/garbage/PaperGarbage.h src/garbage/PlasticGarbage.cpp include/garbage/PlasticGarbage.h include/dustbin/DustbinErrors.hpp src/dustbin/Dustbin.cpp include/dustbin/Dustbin.h src/dustbin/Dustbin9k.cpp include/dustbin/Dustbin9k.h src/garbage/MetalGarbage.cpp include/garbage/MetalGarbage.h src/garbage/BottleCap.cpp include/garbage/BottleCap.h)
add_library(recycling ${RELEASE_SOURCES})
