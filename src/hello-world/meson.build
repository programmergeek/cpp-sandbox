project('hello-world', 'cpp', version: '1.0.0', default_options: ['cpp_std=c++20'])

inc_dirs = include_directories('include')

executable(
  'hello-world',
  sources: ['src/main.cpp', 'src/add.cpp', 'src/math.cpp'],
  install: true,
  include_directories: inc_dirs,
)
