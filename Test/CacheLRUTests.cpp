#include "CacheLRU.h"
#include "gtest/gtest.h"
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>


namespace  {
int get_data(int key) { return key; }
}
int run_test_from_json(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    nlohmann::json test_data;
    file >> test_data;

    int cache_size = test_data["cache_size"];
    std::vector<int> accesses = test_data["accesses"];
    int expected_hits = test_data["expected_hits"];

    MemoryManagement::Cache::CacheLRU<int, int> cache(cache_size);
    int hits = 0;

    for (const auto& key : accesses) {
        if (cache.lookup_update(key, get_data)) {
            ++hits;
        }
    }
    std::cout << "Hits " << hits << std::endl;
    EXPECT_EQ(hits, expected_hits) ;
    return hits;
}


class LRUCacheJSONTests : public ::testing::TestWithParam<std::string> {
    
};

TEST_P(LRUCacheJSONTests, FromJSONFile) {
    std::string jsonFile = GetParam();
    run_test_from_json(jsonFile);
}

std::vector<std::string> collect_json_files() {
    std::vector<std::string> files;
    auto LRU_dir = std::string(TEST_DATA_DIR) + "/LRU/";
    std::cout << "Curent path:" << std::filesystem::current_path() << " test dir: " << LRU_dir <<  std::endl;
    for (const auto& entry :  std::filesystem::directory_iterator(LRU_dir)) {
        if (entry.path().extension() == ".json") {
            files.push_back(entry.path().string());
        }
    }
    return files;
}

INSTANTIATE_TEST_SUITE_P(
    FromFiles,
    LRUCacheJSONTests,
    ::testing::ValuesIn(collect_json_files())
);
