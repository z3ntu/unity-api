if (NOT DEFINED GTEST_ROOT)
    set(GTEST_ROOT /usr/src/gtest)
endif()

set(GTEST_SRC_DIR "${GTEST_ROOT}/src")
set(GTEST_INCLUDE_DIR ${GTEST_ROOT})

add_library(gtest STATIC
${GTEST_SRC_DIR}/gtest-all.cc
${GTEST_SRC_DIR}/gtest_main.cc
)

set_target_properties(gtest PROPERTIES INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIR})

# Clang complains about unused private field 'pretty_' in gtest-internal-inl.h.
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set_target_properties(gtest PROPERTIES COMPILE_FLAGS "-Wno-unused-private-field")
endif()
