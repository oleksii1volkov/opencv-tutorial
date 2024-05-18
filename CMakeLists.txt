cmake_minimum_required(VERSION 3.22.1)

project("OpenCV Tutorial")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(WORKSPACE_DIR "${CMAKE_SOURCE_DIR}")

find_package(OpenCV CONFIG REQUIRED)
find_package(Qt6 CONFIG REQUIRED COMPONENTS Core Gui Widgets Quick QuickControls2 QuickLayouts)

# get_property(importTargetsAfter DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY IMPORTED_TARGETS)
# message(STATUS "Imported Targets: ${importTargetsAfter}")

configure_file(targets/common/config.h.in config.h)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Qt6Core_INCLUDE_DIRS})
include_directories(${Qt6Gui_INCLUDE_DIRS})
include_directories(${Qt6Widgets_INCLUDE_DIRS})
include_directories(${Qt6Quick_INCLUDE_DIRS})
include_directories(${Qt6QuickControls2_INCLUDE_DIRS})
include_directories(${Qt6QuickLayouts_INCLUDE_DIRS})
include_directories(${CMAKE_BINARY_DIR})

add_subdirectory(targets/gstreamer)
add_subdirectory(targets/object_detection)
add_subdirectory(targets/object_tracking)
