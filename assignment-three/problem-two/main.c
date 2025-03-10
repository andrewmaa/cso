#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammar_util.h"


void main(void) {


   char *in_string1="int my_var;";
   char *in_string2="int my_var = 12;";
   char *in_string3="int *my_ptr;";
   char *in_string4="*my_ptr = 10;";
   char *in_string5="int    my_var  =    15432;";
   char *in_string6="int *my_ptr = &my_var;";
   char *in_string7="*my_ptr = &my_var;";




   statement_to_eng(in_string1);
   statement_to_eng(in_string2);
   statement_to_eng(in_string3);
   statement_to_eng(in_string4);
   statement_to_eng(in_string5);
   statement_to_eng(in_string6);
   statement_to_eng(in_string7);
}
