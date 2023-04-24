cmake_minimum_required(VERSION 3.11)

project(OpenCV_Tracker)

# message("==> Using VCPKG")
include(${CMAKE_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake)

set(OpenCV_DIR "${VCPKG_INSTALLED_DIR}/x64-linux/share/opencv3")

# Find OpenCV
find_package(OpenCV REQUIRED)

# Print OpenCV library information
message("OpenCV_DIR: ${OpenCV_DIR}")
message("OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
message("OpenCV_LIBS: ${OpenCV_LIBS}")

# Add executable and link OpenCV libraries
add_executable(${PROJECT_NAME} kcf_multi_tracking.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})

install(
    DIRECTORY Videos
    DESTINATION ${CMAKE_BINARY_DIR}
)
