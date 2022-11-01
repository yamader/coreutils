#include "../coreutils.hh"

auto show_coreutils_help() {
  std::cout <<
    "\n"
    "YamaD's coreutils\n"
    "\n"
    "USAGE\n"
    "  coreutils <command> [options...]\n"
    "\n"
    "COMMANDS\n"
    "  basename    print basename\n"
    "  false       return false\n"
    "  true        return true\n"
    "\n"
    "GLOBAL OPTIONS\n"
    "  -h, --help      show this help\n"
    "  -v, --version   show version\n"
    "\n";
}

auto cmd_coreutils(Context& ctx, Args& args) -> int {
  try { args.parse(); }
  catch(std::invalid_argument& e) {
    Err(ctx) << e.what();
    return 1;
  }

  if(args["help"].flag()) {
    show_coreutils_help();
    return 0;
  }
  if(args["ver"].flag()) {
    show_ver();
    return 0;
  }
  if(args["dbg"].flag()) ctx.debug = true;

  if(args.args.size())  Err(ctx) << "unknown command";
  else                  Err(ctx) << "no commands";
  return 1;
}
