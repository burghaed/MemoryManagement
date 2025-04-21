include(CMakePrintHelpers)

find_package(GTest REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(cache_tests
    CacheLRUTests.cpp
)

target_link_libraries(cache_tests
    GTest::gtest_main
    nlohmann_json::nlohmann_json
    MemoryManagement
)
