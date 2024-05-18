set(INCLUDE_DIRS
    include
    include/qt
    ${WORKSPACE_DIR}/targets/common/include
    ${WORKSPACE_DIR}/targets/common/include/qt
)

set(SOURCE_DIR src)

file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE COMMON_SOURCE_FILES "${WORKSPACE_DIR}/targets/common/src/*.cpp")

file(GLOB_RECURSE QT_HEADER_FILES "include/qt/*.hpp")
file(GLOB_RECURSE COMMON_QT_HEADER_FILES "${WORKSPACE_DIR}/targets/common/include/qt/*.hpp")

qt6_add_resources(RESOURCE_FILES resources/resources.qrc)

set(TARGET_NAME object_tracking)
add_executable(${TARGET_NAME}
    ${COMMON_QT_HEADER_FILES}
    ${QT_HEADER_FILES}
    ${COMMON_SOURCE_FILES}
    ${SOURCE_FILES}
    ${RESOURCE_FILES}
)

target_include_directories(${TARGET_NAME} PRIVATE
    ${INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${Qt6Core_INCLUDE_DIRS}
    ${Qt6Gui_INCLUDE_DIRS}
    ${Qt6Widgets_INCLUDE_DIRS}
    ${Qt6Quick_INCLUDE_DIRS}
    ${Qt6QuickControls2_INCLUDE_DIRS}
    ${Qt6QuickLayouts_INCLUDE_DIRS}
)

target_link_libraries(${TARGET_NAME} PRIVATE
    ${OpenCV_LIBS}
    ${Qt6Core_LIBRARIES}
    ${Qt6Gui_LIBRARIES}
    ${Qt6Widgets_LIBRARIES}
    ${Qt6Quick_LIBRARIES}
    ${Qt6QuickControls2_LIBRARIES}
    ${Qt6QuickLayouts_LIBRARIES}
)

set_target_properties(${TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/targets/${TARGET_NAME}/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/targets/${TARGET_NAME}/Release"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/targets/${TARGET_NAME}/RelWithDebInfo"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/targets/${TARGET_NAME}/MinSizeRel"
)
