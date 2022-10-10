const std = @import("std");
const cmd = @import("../cmd.zig");

pub fn help(writer: cmd.io.out, name: []const u8) void {
    const usage =
        \\Usage: {s} [options] [arguments]
        \\
        \\Options:
    ++ cmd.globalOptsUsage ++
        \\
    ;
    writer.print(usage, .{name}) catch undefined;
}

pub fn exec(_: cmd.io) u8 {
    return 0;
}
