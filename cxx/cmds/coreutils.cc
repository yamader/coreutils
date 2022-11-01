#include "../coreutils.hh"

auto disp_coreutils_help(std::ostream& os = std::cout) -> void {
  disp_ver(os);
  os <<
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

auto cmd_coreutils(Context& ctx, Args& args) -> int {
  args.def_flag("help", "--help", "-h");
  args.def_flag("ver", "--version", "-v");
  try { args.parse(); }
  catch(std::invalid_argument& e) {
    disp_coreutils_help(std::cerr);
    Fatal(ctx) << e.what();
  }

  if(args["help"].flag()) {
    disp_coreutils_help();
    return 0;
  }
  if(args["ver"].flag()) {
    disp_ver();
    return 0;
  }

  disp_coreutils_help(std::cerr);
  return 1;
}
