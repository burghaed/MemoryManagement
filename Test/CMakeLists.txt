include(CMakePrintHelpers)

find_package(GTest REQUIRED)
find_package(nlohmann_json REQUIRED)

set(TEST_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Data/")
cmake_print_variables(TEST_DATA_DIR)

add_executable(cache_tests
    CacheLRUTests.cpp
)

target_link_libraries(cache_tests
    GTest::gtest_main
    nlohmann_json::nlohmann_json
    MemoryManagement
)

target_compile_definitions(cache_tests
    PRIVATE
    TEST_DATA_DIR="${TEST_DATA_DIR}"
)

file(GLOB LRU_JSON_FILES "${TEST_DATA_DIR}/LRU/*.json")

source_group("Data\\LRU" FILES ${LRU_JSON_FILES})
target_sources(cache_tests PRIVATE ${LRU_JSON_FILES})

