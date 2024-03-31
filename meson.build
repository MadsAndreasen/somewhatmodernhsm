project('Modern HSM',
        'cpp',
        version: '2.0.0',
        default_options : ['warning_level=everything',
                           'cpp_std=c++23',
                           'cpp_args=-Wno-abi -Wno-abi-tag -Wno-noexcept'])

cmake = import('cmake')

glog_proj = cmake.subproject('glog', required: true)
glog_dep = glog_proj.dependency('glog')
glog_inc = glog_proj.include_directories('glog')

message('CMake targets:\n - ' + '\n - '.join(glog_proj.target_list()))

subdir('src')
subdir('example/mdoor')
subdir('example/wizard')
subdir('tests')
