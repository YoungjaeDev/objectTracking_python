cmake_minimum_required(VERSION 3.11)

project(OpenCV_Tracker)

# Download and install OpenCV
include(FetchContent)

FetchContent_Declare(
  opencv
  GIT_REPOSITORY https://github.com/opencv/opencv.git
  GIT_TAG        4.5.0
  GIT_SHALLOW    TRUE
  BUILD_COMMAND cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DWITH_TBB=ON -DWITH_OPENMP=ON -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/install
  INSTALL_COMMAND cmake --build build --target install -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/install
)

FetchContent_MakeAvailable(opencv)

message("OpenCV_BINARY_DIR: ${OpenCV_BINARY_DIR}")

# # Set the path to the OpenCVConfig.cmake file
# set(OpenCV_DIR ${OpenCV_BINARY_DIR})

# # Find OpenCV
# find_package(OpenCV REQUIRED)

# # Print OpenCV library information
# message("OpenCV_DIR: ${OpenCV_DIR}")
# message("OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
# message("OpenCV_LIBS: ${OpenCV_LIBS}")

# # Add executable and link OpenCV libraries
# add_executable(${PROJECT_NAME} single_tracking.cpp)
# target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
# target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})
