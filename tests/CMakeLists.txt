project(kestrel-tests)
file(GLOB_RECURSE UNIT_TEST_SOURCES "./*.cpp")
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(kestrel-tests
  ${UNIT_TEST_SOURCES}
)

target_link_libraries(kestrel-tests PRIVATE GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests(kestrel-tests)