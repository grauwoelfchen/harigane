#!/usr/bin/env ruby
# encoding: utf-8

require 'pathname'
root = Pathname.new(__FILE__).realpath.parent.parent
$:.unshift root.join('ext') if $0 == __FILE__

require 'glpk'

lp = Glpk.create_prob
Glpk.set_prob_name(lp, 'sample')
Glpk.set_obj_dir(lp, Glpk::MAX)
Glpk.add_rows(lp, 3)
Glpk.set_row_name(lp, 1, 'p')
Glpk.set_row_bnds(lp, 1, Glpk::UP, 0.0, 100.0)
Glpk.set_row_name(lp, 2, 'q')
Glpk.set_row_bnds(lp, 2, Glpk::UP, 0.0, 600.0)
Glpk.set_row_name(lp, 3, 'r')
Glpk.set_row_bnds(lp, 3, Glpk::UP, 0.0, 300.0)
Glpk.add_cols(lp, 3)
Glpk.set_col_name(lp, 1, 'x1')
Glpk.set_col_bnds(lp, 1, Glpk::LO, 0.0, 0.0)
Glpk.set_obj_coef(lp, 1, 10.0)
Glpk.set_col_name(lp, 2, 'x2')
Glpk.set_col_bnds(lp, 2, Glpk::LO, 0.0, 0.0)
Glpk.set_obj_coef(lp, 2, 6.0)
Glpk.set_col_name(lp, 3, 'x3')
Glpk.set_col_bnds(lp, 3, Glpk::LO, 0.0, 0.0)
Glpk.set_obj_coef(lp, 3, 4.0)
ia = Array(1..1001)
ia[1] = 1
ia[2] = 1
ia[3] = 1
ia[4] = 2
ia[5] = 3
ia[6] = 2
ia[7] = 3
ia[8] = 2
ia[9] = 3
ja = Array(1..1001)
ja[1] = 1
ja[2] = 2
ja[3] = 3
ja[4] = 1
ja[5] = 1
ja[6] = 2
ja[7] = 2
ja[8] = 3
ja[9] = 3
ar = Array(1..1001)
ar[1] = 1.0
ar[2] = 1.0
ar[3] = 1.0
ar[4] = 10.0
ar[5] = 2.0
ar[6] = 4.0
ar[7] = 2.0
ar[8] = 5.0
ar[9] = 6.0
Glpk.load_matrix(lp, 9, ia, ja, ar)
Glpk.simplex(lp, nil)
z = Glpk.get_obj_val(lp)
x1 = Glpk.get_col_prim(lp, 1)
x2 = Glpk.get_col_prim(lp, 2)
x3 = Glpk.get_col_prim(lp, 3)
printf("\nz = %g; x1 = %g; x2 = %g; x3 = %g\n", z, x1, x2, x3)
Glpk.delete_prob(lp)
