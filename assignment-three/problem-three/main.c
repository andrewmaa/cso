#include "grammarx86_util.h"


void main(void) {


   char *in_string1="a+=b;";
   char *in_string2="c++;";
   char *in_string3="d = *e;";
   char *in_string4="*h--;";
   char *in_string5="*j <<= 2;";
   char *in_string6="k <<= n;";
   char *in_string7="p -= q;";
   char *in_string8="r-=s;";
   char *in_string9="t-=128;";
   char *in_string10="u = 256;";
   char *in_string11="v-=512;";


   c_to_x86(in_string1);
   c_to_x86(in_string2);
   c_to_x86(in_string3);
   c_to_x86(in_string4);
   c_to_x86(in_string5);
   c_to_x86(in_string6);
   c_to_x86(in_string7);
   c_to_x86(in_string8);
   c_to_x86(in_string9);
   c_to_x86(in_string10);
   c_to_x86(in_string11);


}
