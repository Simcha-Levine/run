project('Run', 'cpp', version : '0.1', 
  default_options : ['warning_level=3', 'cpp_std=c++20', 'default_library=static'])

sfml = dependency('sfml-graphics')


src = [
  'main.cpp',
  'Game.cpp',
  'GameAction.cpp',
  'Track.cpp',
  'Player.cpp',
  'Line.cpp',
  'Movement.cpp',
  'GBox.cpp',
  'Landscape.cpp',
  'TextureLoader.cpp',
  'Calculations.cpp'
  ]

exe = executable('run', src, install : true, dependencies : [sfml])
# exe = executable('run', src, install : true, link_with : sfml)

test('basic', exe)