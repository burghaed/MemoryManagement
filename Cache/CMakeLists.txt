add_library(MemoryManagement
  	CacheLRU.h CacheLRU.cpp
)

target_include_directories(MemoryManagement PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(MemoryManagement PRIVATE
    -Wall -Wextra -Wpedantic
)