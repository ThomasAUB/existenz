set(EXISTENZ_UNIT_TESTS existenz_tests)

include(CTest)

file(GLOB TARGET_SRC "./tests.cpp" )

add_executable(${EXISTENZ_UNIT_TESTS} ${TARGET_SRC})

add_test(${EXISTENZ_UNIT_TESTS} ${EXISTENZ_UNIT_TESTS})