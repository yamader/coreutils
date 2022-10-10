#pragma once

// https://github.com/yamader/mylib/tree/63aaf8e/cxx/argparse.hh

#include <algorithm>
#include <cstddef>
#include <map>
#include <deque>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace yamad {

using namespace std::literals;

class Args {
  using Key = std::string_view;

  struct Arg {
    std::vector<std::string_view> aliases;
    std::variant<std::string, bool> data;
    bool is_flag = false; // どうにかならんものか

    auto str() -> std::string { return std::get<std::string>(data); }
    auto flag() -> bool { return std::get<bool>(data); }
    auto set(auto&& val) { return data = val; }
  };

  std::map<Key, Arg> arg;
  std::map<std::string_view, Arg*> name; // 参照使いたい
  std::vector<std::string> raw_args;

 public:
  std::deque<std::string> args;

  Args(int argc, char* argv[]): raw_args(argv, argv + argc) {}

  template<class... StringView>
  constexpr auto def(Key key, StringView... aliases) -> void {
    if(arg.contains(key)) throw std::invalid_argument("key already registered");
    arg.insert({ key, { { aliases... } } });
    for(auto alias: { aliases... }) name[alias] = &arg[key];
  }

  template<class... StringView>
  constexpr auto def_flag(Key key, StringView... aliases) -> void {
    if(arg.contains(key)) throw std::invalid_argument("key already registered");
    arg.insert({ key, { { aliases... }, false } });
    arg[key].is_flag = true;
    for(auto alias: { aliases... }) name[alias] = &arg[key];
  }

  auto parse() -> void {
    for(size_t i = 0; i < raw_args.size(); i++) {
      auto& s = raw_args[i];
      if(s.starts_with('-')) {
        if(s.starts_with("--")) {
          if(s == "--") {
            i++;
            for(; i < raw_args.size(); i++) args.push_back(raw_args[i]);
            break;
          }
          auto eq_pos = s.find('=');
          if(eq_pos != std::string::npos) {
            auto key = s.substr(0, eq_pos);
            if(!name.contains(key)) throw std::invalid_argument("invalid option");
            name[key]->data = s.substr(eq_pos + 1);
            continue;
          }
          if(!name.contains(s)) throw std::invalid_argument("invalid option");
          auto& arg = *name[s];
          if(arg.is_flag) {
            arg.data = true;
          } else {
            if(raw_args.size() <= ++i) throw std::invalid_argument("required argument missing");
            arg.data = raw_args[i];
          }
          continue;
        }
        if(s == "-") {
          args.push_back(s);
          continue;
        }
        for(size_t j = 1; j < s.size(); j++) {
          auto key = "-"s + s[j];
          if(!name.contains(key)) throw std::invalid_argument("invalid option");
          auto& arg = *name[key];
          if(arg.is_flag) {
            arg.data = true;
          } else {
            if(s.size() <= ++j) {
              if(raw_args.size() <= ++i) throw std::invalid_argument("required argument missing");
              arg.data = raw_args[i];
            } else {
              auto data = s.substr(j);
              if(data[0] == '=')  arg.data = s.substr(j + 1);
              else                arg.data = data;
            }
            break;
          }
        }
        continue;
      }
      args.push_back(s);
    }
  }

  auto operator[](Key key) -> Arg& { return arg[key]; }
};

}
