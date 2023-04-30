module utils;

import std;

auto gray(string s) => "\33[1;30m" ~ s ~ "\33[0m";
auto red(string s) => "\33[1;31m" ~ s ~ "\33[0m";

void err(A...)(A a) {
  enum pre = red("ERR: ");
  stderr.writeln(pre, a);
}
