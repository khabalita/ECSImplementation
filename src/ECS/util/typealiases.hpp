#pragma once
#include <vector>
#include <unordered_map>

namespace ECS {

template<typename T>
using Vec_t = std::vector<T>;
template<typename KEY_t, typename VALUE_T>
using Hash_t = std::unordered_map<KEY_t, VALUE_T>;

using EntityID_t       = std::size_t;
using ComponentID_t    = std::size_t;
using ComponentTypeID_t = std::size_t;

} //namespace ECS