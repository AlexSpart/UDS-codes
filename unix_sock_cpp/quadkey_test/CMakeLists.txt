cmake_minimum_required(VERSION 3.10)

# set the project name
project(QuadKeyMapper VERSION 1.0)

# seet related optional CMAKE helpers path
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Look up threading library (usually pthread)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads MODULE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/static)

# Mandatory and optional project dependencies
set(Boost_COMPONENTS date_time)
set(Boost_OPTIONAL_COMPONENTS system program_options)
find_package(Boost 1.58 REQUIRED COMPONENTS ${Boost_COMPONENTS})
#include(CompatBoostTargets)
# optional components need to be queried seperately (FindBoost bails out when one is missing)
find_package(Boost 1.58 QUIET OPTIONAL_COMPONENTS ${Boost_OPTIONAL_COMPONENTS})
#include(CompatBoostTargets)

add_subdirectory(quadkeymapper)

#install(TARGETS quadkeymapper EXPORT ${PROJECT_NAME})

#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/quadkeymapper
#  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#  FILES_MATCHING PATTERN "*.hpp" EXCLUDE)


# add the executable
#add_executable(quadkeyservice quadkey_service.cpp)
