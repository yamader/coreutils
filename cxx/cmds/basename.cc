#include "../coreutils.hh"

auto basename_strip(std::string& name, std::string& suff) {
  auto res = basename(name);
  if(res.ends_with(suff)) {
    if(res == suff)
      return res;
    else
      return res.substr(0, res.size() - suff.size());
  }
  return res;
}

auto show_basename_help() {
  std::cout <<
    "\n"
    "print basename\n"
    "\n"
    "USAGE\n"
    "  basename [options...] <name> [suffix]\n"
    " or\n"
    "  basename [options...] <names...>\n"
    "\n"
    "OPTIONS\n"
    "  -a, --multiple          multiple names\n"
    "  -s, --suffix=<suffix>   remove trailing <suffix>; implies -a\n"
    "  -z, --zero              terminate output with NULL\n"
    "  -h, --help              show this help\n"
    "  -v, --version           show version\n"
    "\n";
}

auto cmd_basename(Context& ctx, Args& args) -> int {
  args.def_flag("mult", "--multiple", "-a");
  args.def_flag("zero", "--zero", "-z");
  args.def("suff", "--suffix", "-s");
  try { args.parse(); }
  catch(std::invalid_argument& e) {
    Err(ctx) << e.what();
    return 1;
  }

  if(args["help"].flag()) {
    show_basename_help();
    return 0;
  }
  if(args["ver"].flag()) {
    show_ver();
    return 0;
  }
  if(args["dbg"].flag()) ctx.debug = true;

  struct {
    bool mult;
    bool zero;
    std::string suff;
  } c{
    args["mult"].flag(),
    args["zero"].flag(),
    args["suff"].str(),
  };
  if(!c.suff.empty()) c.mult = true;

  if(c.mult) {
    for(auto name: args.args) {
      std::cout
        << basename_strip(name, c.suff)
        << (c.zero ? '\0' : '\n');
    }
    return 0;
  }

  switch(args.args.size()) {
    case 0: {
      Err(ctx) << "missing operand";
      return 1;
    }
    case 1: {
      std::cout
        << basename(args.args.front())
        << (c.zero ? '\0' : '\n');
      return 0;
    }
    case 2: {
      auto name = args.args.front();
      args.args.pop_front();
      std::cout
        << basename_strip(name, args.args.front())
        << (c.zero ? '\0' : '\n');
      return 0;
    }
    default: {
      Err(ctx) << "too many operands";
      return 1;
    }
  }

  unreachable();
}
