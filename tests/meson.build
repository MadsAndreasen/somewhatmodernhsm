gtest_dep = dependency('gtest', main: true, required: true)

testgtest = executable('testgtest', 'testgtest.cpp', dependencies: gtest_dep)
test('gtest test', testgtest)


testmdoor = executable('testmdoor', ['test_mdoor.cpp', '../example/mdoor/mdoor.cpp'], dependencies: [gtest_dep, hsmlib_dep], include_directories: '../example/mdoor')
test('gtest test', testmdoor)
