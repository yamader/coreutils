import std;

import cmds;
import utils;

enum ver = "v0.0.0";
enum usage = strip(`
coreutils <cmd> [args...]

cmd:
` ~ cmds.cmds.keys.map!`"  "~a`.join('\n') ~ `
`);

int main(string[] args) {
  auto cmd = resolve(args[0].baseName);

  if(!cmd) {
    bool _usage, _ver;

    if(args.length == 1) {
      stderr.writeln(usage);
      return 1;
    }
    foreach(i; 1 .. args.length) {
      auto arg = args[i];

      if(arg.startsWith("--")) {
        if(arg == "--help") { _usage = true; break; }
        if(arg == "--version") { _ver = true; break; }
      } else if(arg.startsWith('-')) {
        if(arg.canFind('h')) { _usage = true; break; }
        if(arg.canFind('v')) { _ver = true; break; }
      } else {
        if((cmd = resolve(arg)) is null) {
          err("command not found: ", arg);
          return 1;
        }
        args = arg ~ args[1..i] ~ args[i+1..$];
        goto run;
      }
    }
    if(_usage) {
      writeln(usage);
      return 0;
    }
    if(_ver) {
      writeln(ver);
      return 0;
    }
    err("invalid option: ", args[1]);
    return 1;
  }

 run:
  return cmd(args);
}
