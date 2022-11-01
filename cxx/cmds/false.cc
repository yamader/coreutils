#include "../coreutils.hh"

auto show_false_help() {
  std::cout <<
    "\n"
    "return false\n"
    "\n"
    "USAGE\n"
    "  false [options...]\n"
    "\n"
    "OPTIONS\n"
    "  -h, --help      show this help\n"
    "  -v, --version   show version\n"
    "\n";
}

auto cmd_false(Context& ctx, Args& args) -> int {
  try { args.parse(); }
  catch(std::invalid_argument& e) {
    Err(ctx) << e.what();
    return 1;
  }

  if(args["help"].flag()) {
    show_false_help();
    return 0;
  }
  if(args["ver"].flag()) {
    show_ver();
    return 0;
  }
  if(args["dbg"].flag()) ctx.debug = true;

  return 1;
}
