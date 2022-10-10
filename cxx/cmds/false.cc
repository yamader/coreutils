#include "cmds.hh"

auto disp_false_help() -> void {
  disp_ver();
  std::cout <<
    "\n"
    "Usage:\n"
    "  coreutils false [options]\n"
    "\n"
    "Options:\n"
    "  -h      show this help\n"
    "  -v      show version\n"
    "\n";
}

auto cmd_false(Args& args) -> int {
  args.def_flag("help", "--help", "-h");
  args.def_flag("ver", "--version", "-v");
  args.parse();

  if(args["help"].flag()) {
    disp_false_help();
    return 0;
  }
  if(args["ver"].flag()) {
    disp_ver();
    return 0;
  }

  return 1;
}
