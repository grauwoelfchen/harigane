#!/usr/bin/env ruby

require 'mkmf'

dir_config('glpk',$sitearchdir, $sitearchdir)
unless have_header('glpk.h')
  puts "\nERROR: GLPK header file is not found, ... aborting :("
  exit -1
end
unless have_library('glpk')
  puts "\nERROR: GLPK library is not found, ... aborting :("
  exit -1
end
create_makefile('glpk')
