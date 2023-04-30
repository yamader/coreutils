module cmds;

public import cmd.false_;
public import cmd.true_;

alias Cmd = int function(string[]);
enum cmds = [
  "false":    &false_,
  "true":     &true_,
];

Cmd resolve(string name) {
  if(name in cmds) return cmds[name];
  else return null;
}
