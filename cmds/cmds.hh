#pragma once

#include "../common.hh"

static auto disp_ver() -> void {
  std::cout << coreutils_v_str << '\n';
}

// commands

using Cmd = std::function<int(Args& args)>;

auto cmd_true(Args& args) -> int;
auto cmd_false(Args& args) -> int;

// todo: constexpr
static std::unordered_map<std::string_view, Cmd> cmds{
  { "true",   cmd_true },
  { "false",  cmd_false },
};
