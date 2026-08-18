#pragma once

#include <string>
#include <vector>
#include <unordered_map>

using String         = std::string;

template<typename tElement>
using List          = std::vector;

template<typename tAccessor, typename tElement>
using UnorderedMap   = std::unordered_map;