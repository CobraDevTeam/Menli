CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

set(CMAKE_BUILD_TYPE Debug)

Project(Menli)

#======================================================================
# Version
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "0")

SET(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

#======================================================================
# Common setup
if (CMAKE_VERSION VERSION_LESS "3.1")
    add_definitions(-std=c++14)
else()
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

#======================================================================

# Recurse to subdirectories
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)
