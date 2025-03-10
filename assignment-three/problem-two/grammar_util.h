// Andrew Ma
// alm8304
// 03/09/2025
// Homework 3, Problem 2


#ifndef GRAMMAR_UTIL_H
#define GRAMMAR_UTIL_H


#endif //GRAMMAR_UTIL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXVAL 100


int sp;
char buffer[MAXVAL];


void push(char f)
{
   if (sp < MAXVAL) {
       buffer[sp++] = f; //add input to stack and inc sp
   }else{
       printf("error: stack full, can't push %c\n", f);
   }
}
/* pop: pop and return top value from stack */
char pop(void)
{
   if (sp > 0) {
       return buffer[--sp]; //
   }else {
       printf("error: stack empty\n");
       return '0';
   }
}




int statement_to_eng(char *in_string) {
   //declare vars


   //get input for next char
   char new_char;
   //count which char of input string we're on
   int counter = 0;
   //if statement declares a var
   int declared = 0;
   //if statement has a pointer left of =
   int ptr_on_left = 0;
   //if statement has a pointer right of =
   int ptr_on_right = 0;
   //if statement makes an assignment with -
   int assignment = 0;
   //if statement uses addressing
   int mem_ref = 0;
   //store var name on left of =
   char left_value[MAXVAL];
   //store var name on right of =
   char right_value[MAXVAL];
   //if right side uses address-of operator
   int address_of = 0;


   //read in next char until we hit end of string char
   while ((new_char = *(in_string+counter)) != '\0') {
       //if we hit a space
       if (new_char == ' ') {
           //check if past input was "int" keyword
           if (assignment == 0 && strncmp(buffer, "int", sp) == 0) {
               //declared a var == True
               declared = 1;
               //reset buffer
               sp = 0;
           // if we hit a space and it's not after the int keyword but
           //     before the =, store it as left var name
           } else if (assignment == 0 && sp > 0) {
               //add in end of string char
               buffer[sp++] = '\0';
               //copy the first sp char of the buffer to left_value
               strncpy(left_value, buffer, sp);
               sp = 0;
           // if we hit a space after the =
           //     store it as right var name
           } else if (assignment == 1 && sp > 0) {
               buffer[sp++] = '\0';
               strncpy(right_value, buffer, sp);
               sp = 0;
           }
           // if new char is a "*"
       } else if (new_char == '*') {
           //if on left side of =
             if (assignment == 0) {
                 //set pointer on left side of = to True
                 ptr_on_left = 1;
                 //if on right side of =
             } else if (assignment == 1) {
                 //set pointer on left side of = to True
                 ptr_on_right = 1;
             }
           //if new char is =
       } else if (new_char == '=') {
             //set has assignment in statement to True
             assignment = 1;
           //store left var name
           if (sp > 0 ){
                 buffer[sp++] = '\0';
                 strncpy(left_value, buffer, sp);
                 sp = 0;
             }
           //if new char is ";"
       } else if (new_char == ';') {
           //if no assignment in statement
           //set left var name
           if (assignment ==0 && sp > 0 ){
               buffer[sp++] = '\0';
               strncpy(left_value, buffer, sp);
               sp = 0;
               //if on right side of =
               //set right var name
           } else if (assignment ==1 && sp > 0) {
               buffer[sp++] = '\0';
               strncpy(right_value, buffer, sp);
               sp = 0;
           }
       } else if (new_char == '&') {
           //set address-of flag
           address_of = 1;
           // Skip the & character so it's not added to the buffer
           counter++;
           continue;
       } else {
           //not a reserved char
           //char is part of var name
           //add to buffer until we've read the whole name
           push(new_char);
       }
       counter++;
   }




   //break into cases
   //multiple each true/false case value by a power of 2
   //to ensure a unique sum for each combination of cases
   int switch_val = declared + 2* ptr_on_left  \
   + 4 * ptr_on_right + 8 * assignment + 16 * mem_ref + 32 * address_of;


   switch(switch_val) {
       case 0:
           printf("Input Statement Empty\n");
           break;
       case 1:
           printf("Declare an Integer named %s\n",left_value);
           break;
       case 3:
           printf("Declare a Pointer to an Integer named %s\n",left_value);
           break;
       case 9:
           printf("Declare an Integer named %s and assign %s to it\n",
               left_value,right_value);
           break;
       case 10:
           printf("Assign %s to the contents of the pointer %s\n",
               right_value,left_value);
           break;
       case 43:  // declared(1) + ptr_on_left(2) + assignment(8) + address_of(32)
           printf("Declare a Pointer to an Integer named %s and assign the address of %s to it\n",
               left_value, right_value);
           break;
       case 42:  // ptr_on_left(2) + assignment(8) + address_of(32)
           printf("Assign the address of %s to the pointer %s\n",
               right_value, left_value);
           break;
       default:
           printf("Case not supported\n");
   }
   sp=0;
   return 0;
}
