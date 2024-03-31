gtest_dep = dependency('gtest', main: true, required: true)

testgtest = executable('testgtest', 'testgtest.cpp', dependencies: gtest_dep)
test('gtest', testgtest)

test_glog = executable('test_glog', 'test_glog.cpp', dependencies: [gtest_dep, glog_dep], include_directories: glog_inc)
test('gtest', test_glog)


testmdoor = executable('testmdoor', ['test_mdoor.cpp', '../example/mdoor/mdoor.cpp'], dependencies: [gtest_dep, hsmlib_dep], include_directories: '../example/mdoor')
test('mdoor', testmdoor)
