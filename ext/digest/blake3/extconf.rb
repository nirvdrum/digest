require "mkmf"

def src_list(path, glob = true)
  srcdir = path.dup
  RbConfig.expand(srcdir) # mutates srcdir :-/
  if glob
    Dir[File.join(srcdir, "*.{#{SRC_EXT.join(%q{,})}}")]
  else
    [srcdir]
  end
end

def add_blake3_source(path)
  should_glob = path.end_with?("/")

  $VPATH << (should_glob ? path : File.dirname(path))
  src_list path, should_glob
end

$srcs = src_list("$(srcdir)") +
    add_blake3_source("$(srcdir)/vendor/blake3.c") +
    add_blake3_source("$(srcdir)/vendor/blake3_dispatch.c") +
    add_blake3_source("$(srcdir)/vendor/blake3_portable.c")

$defs << ['-DBLAKE3_NO_AVX512', '-DBLAKE3_NO_SSE41', '-DBLAKE3_NO_SSE2']

have_header("sys/cdefs.h")

$preload = %w[digest]

create_makefile("digest/blake3")
