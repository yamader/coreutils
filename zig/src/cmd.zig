const std = @import("std");
const mem = std.mem;

pub const globalOptsUsage =
    \\
    \\  --help        show usage
    \\  --version     show version
    \\  --            delimit options and operands
    \\
;

pub const io = struct {
    stdout: out,
    stderr: out,
    stdin: in,

    pub const out = std.fs.File.Writer;
    pub const in = std.fs.File.Reader;
};

const Cmd = struct {
    help: fn (writer: io.out, []const u8) void,
    exec: fn (io: io) u8,

    pub fn from(s: anytype) Cmd {
        return .{
            .help = s.help,
            .exec = s.exec,
        };
    }
};

const cmds = std.ComptimeStringMap(Cmd, .{
    .{ "false", Cmd.from(@import("cmd/false.zig")) },
    .{ "true", Cmd.from(@import("cmd/true.zig")) },
});

fn help(writer: std.fs.File.Writer, name: []const u8) void {
    const usage =
        \\Usage: {s} <command> [options] [arguments]
        \\
        \\Command:
        \\  true
        \\  false
        \\
        \\Options:
    ++ globalOptsUsage ++
        \\
    ;
    writer.print(usage, .{name}) catch undefined;
}

pub fn run(args: [][]u8) u8 {
    const cmd_io = io{
        .stdout = std.io.getStdOut().writer(),
        .stderr = std.io.getStdErr().writer(),
        .stdin = std.io.getStdIn().reader(),
    };

    const name = std.fs.path.basename(args[0]);

    var ret: u8 = 0;

    if (mem.eql(u8, name, "coreutils")) {
        // argparse
        if (args.len >= 2) { //
            const subcmd = args[1];
            if (cmds.has(subcmd)) {
                const cmd = cmds.get(subcmd).?;
                ret = cmd.exec(cmd_io);
            } else {
                help(cmd_io.stderr, "coreutils");
                ret = 1;
            }
        } else {
            help(cmd_io.stdout, name);
            ret = 0;
        }
    } else {
        if (cmds.has(name)) {
            const cmd = cmds.get(name).?;
            ret = cmd.exec(cmd_io);
        } else {
            help(cmd_io.stderr, "coreutils");
            ret = 1;
        }
    }

    return ret;
}
