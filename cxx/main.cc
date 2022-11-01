#include "coreutils.hh"

auto main(int argc, char* argv[]) -> int {
  Args args{argc, argv};
  Context ctx;

  auto name = basename(args.raw_args[0]);
  if(cmds.contains(name)) return cmds[name](ctx, args);
  if(argc < 2)            return cmd_coreutils(ctx, args);

  name = basename(args.raw_args[1]);
  if(cmds.contains(name)) return cmds[name](ctx, args);
  else                    return cmd_coreutils(ctx, args);
}
