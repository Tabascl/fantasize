cmake_minimum_required(VERSION 3.0)

project(fantasize VERSION 0.1.7)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(nlohmann_json 3.7 REQUIRED)
find_package(Boost 1.80 COMPONENTS program_options log log_setup date_time REQUIRED)

find_library(NVML_LIB nvidia-ml)

set(ADDITIONAL_LIBS)

if (NVML_LIB)
    set(HAVE_NVML)

    add_library(nvidia-sensor-lib STATIC
      src/sensor/NvidiaSensor.cxx
      src/sensor/GPUSensorsFacade.cxx)

    target_link_libraries(nvidia-sensor-lib PUBLIC NVML_LIB)

    list(APPEND ADDITIONAL_LIBS nvidia-sensor-lib)
endif()

add_executable(${PROJECT_NAME}
  src/main.cxx
  src/sensor/LMSensorsFacade.cxx
  src/sensor/Sensor.cxx
  src/sensor/LMSensor.cxx
  src/pwm/PWMControl.cxx
  src/pwm/PWMControlFacade.cxx
  src/fan/HwmonFan.cxx
  src/fan/FanCurve.cxx
  src/fan/FanLabeler.cxx
  src/FanGenerator.cxx
  src/Serializer.cxx
  src/sensor/SensorManager.cxx
  src/Controller.cxx
  src/Settings.cxx
  src/App.cxx
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_include_directories(${PROJECT_NAME} PUBLIC include /opt/cuda)

target_link_libraries(${PROJECT_NAME} PUBLIC sensors nlohmann_json::nlohmann_json tbb ${Boost_LIBRARIES} ${ADDITIONAL_LIBS})

install(TARGETS ${PROJECT_NAME} DESTINATION usr/local/bin)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/unit/fantasize.service DESTINATION usr/lib/systemd/system)
