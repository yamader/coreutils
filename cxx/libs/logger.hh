#pragma once

// https://github.com/yamader/mylib/tree/473575c/cxx/logger.hh

#include "context.hh"
#include "nullstream.hh"

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace yamad {

using namespace std::literals;

constexpr inline std::string_view logger_prefix{"coreutils: "};

auto c_dim(Context& ctx, auto&& msg) -> decltype(msg + "") {
  if(ctx.has_color) return "\e[1;30m" + msg + "\e[0m";
  else              return msg;
}

auto c_err(Context& ctx, auto&& msg) -> decltype(msg + "") {
  if(ctx.has_color) return "\e[1;31m" + msg + "\e[0m";
  else              return msg;
}

class Logger {
  std::stringstream ss;
  std::ostream& os;

 public:
  Logger(std::ostream& os): os{os} { ss << logger_prefix; }
  ~Logger() { os << ss.str() << '\n'; }

  template<typename T>
  auto operator<<(T&& val) -> Logger& {
    ss << std::forward<T>(val);
    return *this;
  }
};

class Log {
  Logger logger;
  Context& ctx;

 public:
  Log(Context& ctx): logger{std::cout}, ctx{ctx} {}

  template<typename T>
  auto operator<<(T&& val) -> Log& {
    logger << std::forward<T>(val);
    return *this;
  }
};

class Err {
  Logger logger;
  Context& ctx;

 public:
  Err(Context& ctx): logger{std::cerr}, ctx{ctx} {
    logger << c_err(ctx, "error: "s);
  }

  template<typename T>
  auto operator<<(T&& val) -> Err& {
    logger << std::forward<T>(val);
    return *this;
  }
};

class Fatal {
  Logger logger;
  Context& ctx;

 public:
  Fatal(Context& ctx): logger{std::cerr}, ctx{ctx} {
    logger << c_err(ctx, "fatal: "s);
  }
  [[noreturn]] ~Fatal() {
    logger.~Logger();
    exit(1);
  }

  template<typename T>
  auto operator<<(T&& val) -> Fatal& {
    logger << std::forward<T>(val);
    return *this;
  }
};

class Debug {
  Logger logger;
  Context& ctx;

  auto switch_os(Context& ctx) -> std::ostream& {
    if(ctx.debugging) return std::cout;
    else              return yamad::null_stream;
  }

 public:
  Debug(Context& ctx): logger{switch_os(ctx)}, ctx{ctx} {
    logger << c_dim(ctx, "debug: "s);
  }

  template<typename T>
  auto operator<<(T&& val) -> Debug& {
    logger << std::forward<T>(val);
    return *this;
  }
};

}
