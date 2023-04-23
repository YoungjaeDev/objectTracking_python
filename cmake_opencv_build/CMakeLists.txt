cmake_minimum_required(VERSION 3.11)

project(OpenCV_Tracker)

# message("==> Using VCPKG")
# include(${CMAKE_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake)

# # Set the path to the OpenCVConfig.cmake file
# set(OpenCV_DIR ${OpenCV_BINARY_DIR})

# # Find OpenCV
find_package(OpenCV REQUIRED)

# # Print OpenCV library information
# message("OpenCV_DIR: ${OpenCV_DIR}")
# message("OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
# message("OpenCV_LIBS: ${OpenCV_LIBS}")

# # Add executable and link OpenCV libraries
add_executable(${PROJECT_NAME} print_opencv_info.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
