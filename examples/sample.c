#include <stdio.h>
#include <stdlib.h>
#include <glpk.h>

int main(void) {
  glp_prob *lp;
  lp = glp_create_prob();
  glp_set_prob_name(lp, "sample");
  glp_set_obj_dir(lp, GLP_MAX);
  glp_add_rows(lp, 3);
  return 0;
}
