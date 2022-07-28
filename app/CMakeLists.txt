cmake_minimum_required(VERSION 3.0)

project(fantasize)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(app
  src/main.cxx
  src/nvidia.cxx
  src/pwm.cxx
)

set_property(TARGET app PROPERTY CXX_STANDARD 17)

target_include_directories(app PUBLIC include /opt/cuda)
target_link_libraries(app PUBLIC sensors nvidia-ml)
