#pragma once

#include <list>
#include <unordered_map>

namespace MemoryManagement {
namespace Cache {
    
template <typename T, typename key_t = int> class CacheLRU {
  size_t size_ = 0;
  std::list<std::pair<key_t, T>> cache_;

  using list_it_t = typename std::list<std::pair<key_t, T>>::iterator;
  std::unordered_map<key_t, list_it_t> hash_;

public:
  CacheLRU(size_t sz) : size_(sz) {}

  bool is_full() const { return (cache_.size() == size_); }

  template <typename get_data_t>
  bool lookup_update(const key_t &key, get_data_t get_data) {
    auto hit = hash_.find(key);
    if (hit == hash_.end()) {
      if (is_full()) {
        hash_.erase(cache_.back().first);
        cache_.pop_back();
      }
      cache_.emplace_front(key, get_data(key));
      hash_.emplace(key, cache_.begin());
      return false;
    }

    auto it = hit->second;
    cache_.splice(cache_.begin(), cache_, it);
    return true;
  }
};

} // namespace Cache
} // namespace MemoryManagement
