# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

cmake_minimum_required(VERSION 3.24)

project(Embedded_C_++)

set(TEST_DIR ${PROJECT_SOURCE_DIR}/test-framework)

# Add tasks subprojects
include(cmake/utils.cmake)
add_subprojects(${PROJECT_SOURCE_DIR})