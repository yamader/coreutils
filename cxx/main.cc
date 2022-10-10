#include "common.hh"
#include "cmds/cmds.hh"

auto disp_main_help() -> void {
  disp_ver();
  std::cout <<
    "\n"
    "Usage:\n"
    "  coreutils [command] [options]\n"
    "\n"
    "Commands:\n"
    "  true    return true\n"
    "  false   return false\n"
    "\n"
    "Options:\n"
    "  -h      show this help\n"
    "  -v      show version\n"
    "\n";
}

auto cmd_main(Args& args) -> int {
  args.def_flag("help", "--help", "-h");
  args.def_flag("ver", "--version", "-v");
  args.parse();

  if(args["help"].flag()) {
    disp_main_help();
    return 0;
  }
  if(args["ver"].flag()) {
    disp_ver();
    return 0;
  }

  disp_main_help();
  return 1;
}

auto main(int argc, char* argv[]) -> int {
  Args args{argc, argv};

  // argsを使ったやつに書き換える
  if(cmds.contains(argv[0]))  return cmds[argv[0]](args);
  if(argc < 2)                return cmd_main(args);
  if(cmds.contains(argv[1]))  return cmds[argv[1]](args);
  else                        return cmd_main(args);
}
