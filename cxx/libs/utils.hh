#pragma once

// https://github.com/yamader/mylib/tree/5e01fda/cxx/utils.hh

[[noreturn]] inline auto unreachable() {
  __builtin_unreachable();
}
