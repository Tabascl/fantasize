cmake_minimum_required(VERSION 3.0)

project(fantasize)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(nlohmann_json 3.11.2 REQUIRED)

add_executable(app
  src/main.cxx
  src/sensor/SensorsWrapper.cxx
  src/sensor/Sensor.cxx
  src/sensor/NvidiaSensor.cxx
  src/sensor/HwmonSensor.cxx
  src/fan/Pwm.cxx
  src/fan/PwmControl.cxx
  src/fan/HwmonFan.cxx
  src/Mapping.cxx
  src/Serializer.cxx
)

set_property(TARGET app PROPERTY CXX_STANDARD 17)

target_include_directories(app PUBLIC include /opt/cuda)
target_link_libraries(app PUBLIC sensors nvidia-ml nlohmann_json::nlohmann_json)
