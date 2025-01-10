#!/usr/bin/env ruby

require 'tmpdir'

BLAKE3_VERSION = ENV["BLAKE3_VERSION"] || "1.5.5"

Dir.mktmpdir do |dir|
  Dir.chdir(dir) do
    system("git", "clone", "--depth", "1", "--branch", BLAKE3_VERSION, "https://github.com/BLAKE3-team/BLAKE3.git")

    Dir["BLAKE3/c/blake3*.{c,h,asm,S}"].each do |file|
      destination = File.join(__dir__, "vendor", File.basename(file))
      FileUtils.mv(file, destination)
    end
  end
end
