if(EXISTS "/home/saskeli/bv_testing/tests/tests[1]_tests.cmake")
  include("/home/saskeli/bv_testing/tests/tests[1]_tests.cmake")
else()
  add_test(tests_NOT_BUILT tests_NOT_BUILT)
endif()
