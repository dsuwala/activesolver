#####################################################################################
# MIT License                                                                       #
#                                                                                   #
# Copyright (c) Dominik Suwała, d.suwala@student.uw.edu.pl 2022                     #
# based on version by Dr. Daniel Alejandro Matoz Fernandez fdamatoz@gmail.com       #
#                                                                                   #
# Permission is hereby granted, free of charge, to any person obtaining a copy      #
# of this software and associated documentation files (the "Software"), to deal     #
# in the Software without restriction, including without limitation the rights      #
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell         #
# copies of the Software, and to permit persons to whom the Software is             #
# furnished to do so, subject to the following conditions:                          #
#                                                                                   #
# The above copyright notice and this permission notice shall be included in all    #
# copies or substantial portions of the Software.                                   #
#                                                                                   #
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR        #
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,          #
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE       #
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER            #
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,     #
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE     #
# SOFTWARE.                                                                         #
#####################################################################################
#main CMakeLists.txt

CMAKE_MINIMUM_REQUIRED(VERSION 3.16 FATAL_ERROR)

########### ADD C++ SUPPORT  ##############
set(CMAKE_CXX_STANDARD 14)
find_program(CMAKE_C_COMPILER NAMES $ENV{CC} gcc PATHS ENV PATH NO_DEFAULT_PATH)
find_program(CMAKE_CXX_COMPILER NAMES $ENV{CXX} g++ PATHS ENV PATH NO_DEFAULT_PATH)
set(CMAKE_CXX_STANDARD 14)

project (TESTSUITE C CXX)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

########### SET C++ COMPILER FLAGS  ############
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g -ggdb -Wall -std=c++14" CACHE STRING "Flags used by the compiler during debug builds." FORCE)
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -Wall -DNDEBUG" CACHE STRING "Flags used by the compiler during minimum size release builds." FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -funroll-loops -ffast-math -DNDEBUG -std=c++14 -fvisibility=hidden -fpermissive" CACHE STRING "Flags used by the compiler during release builds." FORCE)
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -O -funroll-loops -ffast-math -DNDEBUG -Wall" CACHE STRING "Flags used by the compiler during release builds with debug info." FORCE)
################################################

###########SUPPLY SOURCE FILES #################
SET(TMP_HDR_DIR "${TESTSUITE_SOURCE_DIR}/include/")
SET(TMP_SRC_DIR "${TESTSUITE_SOURCE_DIR}/src/")

file(GLOB TMP_HDRS ${TMP_HDR_DIR}/*.hpp)
file(GLOB TMP_SRCS ${TMP_SRC_DIR}/*.cpp)
################################################

# create temporary cpp library to be linked against gtest --> NO pybind here yet
add_library(tmplib SHARED ${TMP_SRCS}) 
target_include_directories(tmplib PRIVATE ${TMP_HDR_DIR})

# create second temporary cpp library to be linked against gtest for debug --> NO pybind here yet
add_library(tmplib2 SHARED ${TMP_SRCS}) 
target_include_directories(tmplib2 PRIVATE ${TMP_HDR_DIR})

########### GOOGLE TEST SETUP #############
enable_testing()
add_subdirectory(test)
###########################################

########### PYBIND ########################
add_subdirectory(pybind)
###########################################
