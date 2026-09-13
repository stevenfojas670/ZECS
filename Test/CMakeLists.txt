include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.9.1
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(Catch2)

add_executable(Test
    Entities/EntityManager_Tests.cpp
    Components/ComponentStorage_Tests.cpp
    Components/ComponentManager_Tests.cpp
    Systems/SystemManager_Tests.cpp
    Systems/Systems.h
)

# Test/ is the include root for test-only headers, so files in any subfolder
# reach shared helpers as "Helpers.h" rather than a relative ../ path.
target_include_directories(Test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Catch2WithMain supplies main(), so no test file declares one.
target_link_libraries(Test PRIVATE ZECS Catch2::Catch2WithMain)

# catch_discover_tests ships in Catch2's extras/, not in CMake itself. It runs
# Test.exe at build time to enumerate TEST_CASEs and registers each with CTest,
# so a crash fails one test rather than the whole run.
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(Test)
