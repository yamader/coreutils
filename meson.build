project('coreutils', 'd')

add_project_arguments('-preview=shortenedMethods', language: 'd')
inc = include_directories('src')

src = files(
  'src/main.d',
  'src/cmds.d',
  'src/utils.d',
  'src/cmd/false_.d',
  'src/cmd/true_.d',
)

executable('coreutils', src,
  include_directories: inc)
