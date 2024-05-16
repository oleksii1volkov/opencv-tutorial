set(SOURCE_DIR src)
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp")

set(TARGET_NAME object_tracking)
add_executable(${TARGET_NAME} ${SOURCE_FILES})
target_include_directories(${TARGET_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} ${OpenCV_LIBS})
