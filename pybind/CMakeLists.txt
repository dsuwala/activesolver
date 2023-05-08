# pybind cmake 

CMAKE_MINIMUM_REQUIRED(VERSION 3.16 FATAL_ERROR)

###########SUPPLY SOURCE FILES ################
SET(TMP_HDR_DIR "${TESTSUITE_SOURCE_DIR}/include/")
SET(TMP_SRC_DIR "${TESTSUITE_SOURCE_DIR}/src/")
file(GLOB TMP_HDRS ${TMP_HDR_DIR}/*.hpp)
file(GLOB TMP_SRCS ${TMP_SRC_DIR}/*.cpp)
include_directories(${TMP_HDR_DIR})
##############################################

####### python wrapper files #################
SET(PYBIND_SRC_DIR "${TESTSUITE_SOURCE_DIR}/pybind")
file(GLOB PYTHON_FILES "${PYBIND_SRC_DIR}/pybindexport.cpp" "${PYBIND_SRC_DIR}/*.hpp")
include_directories(${PYBIND_SRC_DIR})
# ############################################

########### ADD PYBIND SUPPORT  ##############
find_package(pybind11 REQUIRED)
set(PYBIND11_PYTHON_VERSION 3.8 CACHE STRING "")
set(PYBIND11_CPP_STANDARD -std=c++14)
##############################################

############ CREATE PYTHON MODULE ############
add_library(activeSolver SHARED ${TMP_SRCS} "${TESTSUITE_SOURCE_DIR}/pybind/pybindexport.cpp")
target_link_libraries(activeSolver PRIVATE pybind11::module ${THREAD_LIB}) 
set_target_properties(activeSolver PROPERTIES PREFIX ""  OUTPUT_NAME "activeSolver" SUFFIX ".so" CXX_STANDARD 14)
##############################################
