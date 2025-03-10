#include <stdio.h>
#include "color_util.h"




int main() {
   color_node *red = init_with_primary();
   printf("Print primary color wheel:\n");
   print_wheel(red);
   mix_with_neighbor(red->next->next);
   mix_with_neighbor(red->next);
   mix_with_neighbor(red);
   mix_with_neighbor(red);
   printf("Print after adding colors:\n");
   print_wheel(red);
   return 0;
}
