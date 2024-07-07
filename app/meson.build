project('fantasize', 'cpp', version : '0.3.0', default_options : 'cpp_std=c++20')

src = [
  'src/main.cxx',
  'src/sensor/LMSensorsFacade.cxx',
  'src/sensor/Sensor.cxx',
  'src/sensor/LMSensor.cxx',
  'src/pwm/PWMControl.cxx',
  'src/pwm/PWMControlFacade.cxx',
  'src/fan/HwmonFan.cxx',
  'src/fan/FanCurve.cxx',
  'src/fan/FanLabeler.cxx',
  'src/fan/Aggregators.cxx',
  'src/FanGenerator.cxx',
  'src/Serializer.cxx',
  'src/sensor/SensorManager.cxx',
  'src/Controller.cxx',
  'src/Settings.cxx',
  'src/App.cxx'
]

deps = [
  dependency('nlohmann_json'),
  dependency('boost', modules : ['program_options', 'log', 'log_setup', 'date_time', 'thread']),
  dependency('tbb'),
  meson.get_compiler('cpp').find_library('sensors')
]

inc = include_directories('include')

exe = executable('fantasize',
  src,
  dependencies: deps,
  install: true,
  include_directories: inc)

install_data('unit/fantasize.service', install_dir : '/usr/lib/systemd/system')
