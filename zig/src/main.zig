const std = @import("std");
const cmd = @import("cmd.zig");

pub fn main() !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    const args = try std.process.argsAlloc(allocator);
    const ret = cmd.run(args);

    std.process.exit(ret);
}
