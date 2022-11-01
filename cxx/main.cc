#include "coreutils.hh"

auto main(int argc, char* argv[]) -> int {
  Args args{argc, argv};
  Context ctx;

  // global opts
  args.def_flag("help", "--help", "-h");
  args.def_flag("ver", "--version", "-v");
  args.def_flag("dbg", "--debug");

  auto name = ctx.name = basename(args.raw_args[0]);
  if(cmds.contains(name)) return cmds[name](ctx, args);
  if(argc < 2)            return cmd_coreutils(ctx, args);

  auto sub = basename(args.raw_args[1]);
  if(cmds.contains(sub)) {
    ctx.name = sub;
    args.skip = 2;
    return cmds[sub](ctx, args);
  }

  return cmd_coreutils(ctx, args);
}
