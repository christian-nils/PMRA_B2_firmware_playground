cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set(CMAKE_C_STANDARD 99)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/cmake/arm-gcc-cortex-m4.cmake)

include(cmake/utilities.cmake)

project(MicroROS C ASM)

include(ExternalProject)

if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
    set(submake "$(MAKE)")
else()
    set(submake "make")
endif()

externalproject_add(libmicroros_project
    PREFIX     ${CMAKE_BINARY_DIR}/libmicroros-prefix
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}
    BINARY_DIR ${CMAKE_CURRENT_LIST_DIR}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND
        ${submake} -j -f libmicroros.mk
            X_CC=${CMAKE_C_COMPILER}
            X_AR=${CMAKE_AR}
            X_STRIP=${CMAKE_STRIP}
            X_CFLAGS=${CMAKE_C_FLAGS}
            X_CXX=${CMAKE_CXX_COMPILER}
            X_CXXFLAGS=${CMAKE_CXX_FLAGS}
            BUILD_DIR=${CMAKE_BINARY_DIR}
            APP_COLCON_META=${APP_COLCON_META}
    INSTALL_COMMAND ""
    BUILD_BYPRODUCTS ${CMAKE_CURRENT_LIST_DIR}/libmicroros.a
    )

# micro-ROS Library

add_library(libmicroros-prebuilt INTERFACE)

add_dependencies(libmicroros-prebuilt libmicroros_project)

target_link_libraries(libmicroros-prebuilt INTERFACE ${CMAKE_CURRENT_LIST_DIR}/libmicroros.a)
target_include_directories(libmicroros-prebuilt INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

execute_process(
    COMMAND
        ${submake} -j -f libmicroros.mk get_package_names
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE
        INCLUDE_ROS2_PACKAGES
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )

foreach(pkg ${INCLUDE_ROS2_PACKAGES})
    target_include_directories(libmicroros-prebuilt INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include/${pkg})
endforeach()