#pragma once

#include "libs/argparse.hh"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

using namespace std::literals;
using namespace yamad;

constexpr inline auto coreutils_v_major{0};
constexpr inline auto coreutils_v_minor{1};
constexpr inline auto coreutils_v_patch{0};
constexpr inline auto coreutils_v_str{"v0.1.0"sv};
