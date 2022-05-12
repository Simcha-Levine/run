project('Run', 'cpp', version : '0.1', 
  default_options : ['warning_level=3', 'cpp_std=c++20', 'default_library=static'])

sfml = [dependency('sfml-graphics'),
 dependency('sfml-window'),
  dependency('sfml-system'),
  dependency('sfml-audio')]


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

test('basic', exe)