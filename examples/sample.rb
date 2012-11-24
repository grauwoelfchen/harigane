#!/usr/bin/env ruby
# encoding: utf-8

require 'pathname'
root = Pathname.new(__FILE__).realpath.parent.parent
$:.unshift root.join('ext') if $0 == __FILE__

require 'glpk'

lp = Glpk.create_prob
Glpk.set_prob_name(lp, 'sample')
Glpk.set_obj_dir(lp, 2)

p Glpk.get_prob_name(lp)
p Glpk.get_obj_dir(lp)
