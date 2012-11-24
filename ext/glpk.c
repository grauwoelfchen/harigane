#include <ruby.h>
#include "glpk.h"

// module
static VALUE wrap_glp_version(VALUE self) {
  const char *res;
  res = glp_version();
  return rb_str_new2(res);
}
static VALUE wrap_glp_free_env(VALUE self) {
  int res;
  res = glp_free_env();
  return INT2NUM(res);
}
static VALUE wrap_glp_create_prob(VALUE self) {
  glp_prob *lp;
  ID id;
  VALUE klass;
  lp = (glp_prob *) glp_create_prob();
  id = rb_intern("Problem");
  klass = rb_const_get(self, id);
  return Data_Wrap_Struct(klass, NULL, NULL, lp);
}
static VALUE wrap_glp_set_prob_name(VALUE self, VALUE P, VALUE name) {
  glp_prob *lp;
  Data_Get_Struct(P, glp_prob, lp);
  glp_set_prob_name(lp, (const char *)StringValuePtr(name));
  return Qnil;
}
static VALUE wrap_glp_get_prob_name(VALUE self, VALUE P) {
  const char *res;
  glp_prob *lp;
  Data_Get_Struct(P, glp_prob, lp);
  res = glp_get_prob_name(lp);
  return rb_str_new2(res);
}
static VALUE wrap_glp_set_obj_dir(VALUE self, VALUE P, VALUE dir) {
  glp_prob *lp;
  Data_Get_Struct(P, glp_prob, lp);
  glp_set_obj_dir(lp, NUM2INT(dir));
  return Qnil;
}
static VALUE wrap_glp_get_obj_dir(VALUE self, VALUE P) {
  int res;
  glp_prob *lp;
  Data_Get_Struct(P, glp_prob, lp);
  res = glp_get_obj_dir(lp);
  return INT2NUM(res);
}
static VALUE wrap_glp_set_obj_coef(VALUE self, VALUE P, VALUE j, VALUE coef) {
  glp_prob *lp;
  Data_Get_Struct(P, glp_prob, lp);
  glp_set_obj_coef(lp, NUM2INT(j), NUM2DBL(coef));
  return Qnil;
}
static VALUE wrap_glp_add_rows(VALUE self, VALUE P, VALUE nrs) {
  int res;
  glp_prob *lp;
  Data_Get_Struct(P, glp_prob, lp);
  res = glp_add_rows(lp, NUM2INT(nrs));
  return INT2NUM(res);
}
static VALUE wrap_glp_set_row_name(VALUE self, VALUE P, VALUE i, VALUE name) {
  glp_prob *lp;
  Data_Get_Struct(P, glp_prob, lp);
  glp_set_row_name(lp, NUM2INT(i), (const char *)StringValuePtr(name));
  return Qnil;
}
static VALUE wrap_glp_set_row_bnds(
    VALUE self, VALUE P, VALUE i, VALUE type, VALUE lb, VALUE ub) {
  glp_prob *lp;
  Data_Get_Struct(P, glp_prob, lp);
  glp_set_row_bnds(
    lp,
    NUM2INT(i),
    NUM2INT(type),
    NUM2DBL(lb),
    NUM2DBL(ub)
  );
  return Qnil;
}
static VALUE wrap_glp_add_cols(VALUE self, VALUE P, VALUE ncs) {
  int res;
  glp_prob *lp;
  Data_Get_Struct(P, glp_prob, lp);
  res = glp_add_cols(lp, NUM2INT(ncs));
  return INT2NUM(res);
}
static VALUE wrap_glp_set_col_name(VALUE self, VALUE P, VALUE i, VALUE name) {
  glp_prob *lp;
  Data_Get_Struct(P, glp_prob, lp);
  glp_set_col_name(lp, NUM2INT(i), (const char *)StringValuePtr(name));
  return Qnil;
}
static VALUE wrap_glp_set_col_bnds(
    VALUE self, VALUE P, VALUE j, VALUE type, VALUE lb, VALUE ub) {
  glp_prob *lp;
  Data_Get_Struct(P, glp_prob, lp);
  glp_set_col_bnds(
    lp,
    NUM2INT(j),
    NUM2INT(type),
    NUM2DBL(lb),
    NUM2DBL(ub)
  );
  return Qnil;
}
static VALUE wrap_glp_load_matrix(
    VALUE self, VALUE P, VALUE ne, VALUE ia, VALUE ja, VALUE ar) {
  glp_prob *lp;
  Data_Get_Struct(P, glp_prob, lp);
  glp_load_matrix(
    lp,
    NUM2INT(ne),
    (int const (*))RARRAY(ia),
    (int const (*))RARRAY(ja),
    (double const (*))RARRAY(ar)
  );
  return Qnil;
}

// klass
static VALUE wrap_glp_prob_allocate(VALUE self) {
  glp_prob *lp = ALLOC(glp_prob);
  return Data_Wrap_Struct(self, 0, -1, lp);
}
static VALUE wrap_new_glp_prob(VALUE self) {
  glp_prob *lp;
  Data_Get_Struct(self, glp_prob, lp);
  return self;
}

void Init_glpk() {
  VALUE module;
  VALUE klass;
  // module
  module = rb_define_module("Glpk");
  rb_define_const(module, "MIN", INT2NUM((int)(1)));
  rb_define_const(module, "MAX", INT2NUM((int)(2)));
  rb_define_const(module, "LO",  INT2NUM((int)(2)));
  rb_define_const(module, "UP",  INT2NUM((int)(3)));
  rb_define_module_function(module, "version", wrap_glp_version, 0);
  rb_define_module_function(module, "free_env", wrap_glp_free_env, 0);
  rb_define_module_function(module, "create_prob", wrap_glp_create_prob, 0);
  rb_define_module_function(module, "set_prob_name", wrap_glp_set_prob_name, 2);
  rb_define_module_function(module, "get_prob_name", wrap_glp_get_prob_name, 1);
  rb_define_module_function(module, "set_obj_dir", wrap_glp_set_obj_dir, 2);
  rb_define_module_function(module, "get_obj_dir", wrap_glp_get_obj_dir, 1);
  rb_define_module_function(module, "set_obj_coef", wrap_glp_set_obj_coef, 3);
  rb_define_module_function(module, "add_rows", wrap_glp_add_rows, 2);
  rb_define_module_function(module, "set_row_name", wrap_glp_set_row_name, 3);
  rb_define_module_function(module, "set_row_bnds", wrap_glp_set_row_bnds, 5);
  rb_define_module_function(module, "add_cols", wrap_glp_add_cols, 2);
  rb_define_module_function(module, "set_col_name", wrap_glp_set_col_name, 3);
  rb_define_module_function(module, "set_col_bnds", wrap_glp_set_col_bnds, 5);
  rb_define_module_function(module, "load_matrix", wrap_glp_load_matrix, 5);
  // klass
  klass = rb_define_class_under(module, "Problem", rb_cObject);
  rb_define_alloc_func(klass, wrap_glp_prob_allocate);
  rb_define_private_method(klass, "initialize", wrap_new_glp_prob, 0);
}
