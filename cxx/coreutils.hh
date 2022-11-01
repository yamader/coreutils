#pragma once

#include "libs/argparse.hh"
#include "libs/context.hh"
#include "libs/logger.hh"
#include "libs/utils.hh"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

using namespace std::literals;
using namespace yamad;

constexpr inline auto coreutils_v_major{0};
constexpr inline auto coreutils_v_minor{1};
constexpr inline auto coreutils_v_patch{0};
constexpr inline auto coreutils_v_str{"v0.1.0"sv};

inline auto show_ver(std::ostream& os = std::cout) {
  os << "coreutils " << coreutils_v_str << '\n';
}

// functions

inline auto basename(std::string_view path) -> std::string_view {
  if(path.size() <= 1)    return path;
  if(path.ends_with('/')) return basename(path.substr(0, path.size() - 1));
  else                    return path.substr(path.find_last_of('/') + 1);
}

// commands

using Cmd = std::function<int(Context& ctx, Args& args)>;

auto cmd_coreutils(Context& ctx, Args& args) -> int;

auto cmd_basename(Context& ctx, Args& args) -> int;
auto cmd_false(Context& ctx, Args& args) -> int;
auto cmd_true(Context& ctx, Args& args) -> int;

inline std::unordered_map<std::string_view, Cmd> cmds{
  { "basename",   cmd_basename },
  { "false",      cmd_false },
  { "true",       cmd_true },
};
