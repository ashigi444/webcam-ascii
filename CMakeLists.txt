cmake_minimum_required(VERSION 3.10)
project(WebcamASCII VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#opencv finder
find_package(OpenCV REQUIRED)

#exe creation
add_executable(webcam-ascii webcam-ascii.cpp)

#link opencv
target_link_libraries(webcam-ascii ${OpenCV_LIBS})

#tar install
install(TARGETS webcam-ascii DESTINATION bin)

#info printing
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")