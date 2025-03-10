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
#include <ctype.h>
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




int c_to_x86(char *in_string) {
    char new_char;
    int counter = 0;
    char left_value[MAXVAL];
    char right_value[MAXVAL];
    int buffer_has_op = 0;
    
    // Operation types
    enum op_type {
        NONE,
        ASSIGN,         // =
        INCREMENT,      // ++
        DECREMENT,     // --
        LEFT_SHIFT,    // <<=
        ADD,           // +=
        SUBTRACT,      // -=
        POINTER_DEREF  // *
    } operation = NONE;
    
    // Reset buffer
    sp = 0;
    
    // Parse the input string
    while ((new_char = *(in_string+counter)) != '\0') {
        if (new_char == ' ') {
            if (sp > 0) {
                buffer[sp] = '\0';
                if (!buffer_has_op) {
                    if (operation == NONE) {
                        strncpy(left_value, buffer, sp);
                    } else {
                        strncpy(right_value, buffer, sp);
                    }
                }
                sp = 0;
                buffer_has_op = 0;
            }
        } else if (new_char == '+' && *(in_string+counter+1) == '+') {
            operation = INCREMENT;
            buffer_has_op = 1;
            counter++;
        } else if (new_char == '-' && *(in_string+counter+1) == '-') {
            operation = DECREMENT;
            buffer_has_op = 1;
            counter++;
        } else if (new_char == '<' && *(in_string+counter+1) == '<') {
            buffer_has_op = 1;
            counter++;
        } else if (new_char == '=') {
            if (*(in_string+counter-1) == '<' && *(in_string+counter-2) == '<') {
                operation = LEFT_SHIFT;
            } else if (*(in_string+counter-1) == '+') {
                operation = ADD;
            } else if (*(in_string+counter-1) == '-') {
                operation = SUBTRACT;
            } else {
                operation = ASSIGN;
            }
            if (sp > 0 && !buffer_has_op) {
                buffer[sp] = '\0';
                strncpy(left_value, buffer, sp);
            }
            sp = 0;
            buffer_has_op = 0;
        } else if (new_char == '*') {
            operation = POINTER_DEREF;
        } else if (new_char != ';') {
            push(new_char);
        }
        counter++;
    }
    
    // Get final value if any
    if (sp > 0) {
        buffer[sp] = '\0';
        strncpy(right_value, buffer, sp);
    }
    

    
    switch(operation) {
        case ASSIGN:
            if (isdigit(right_value[0])) {
                // Copy constant to var: a = 10;
                printf("    movq $%s, %%rax\n", right_value);
            } else {
                // Copy var to var: b = a;
                printf("    movq %%rax, %%rbx\n");
            }
            break;
            
        case POINTER_DEREF:
            // Copy data at memory location to var: b = *a_ptr;
            printf("    movq (%%rax), %%rbx\n");
            break;
            
        case INCREMENT:
            if (operation == POINTER_DEREF) {
                // Increment data at memory location: (*a)++;
                printf("    incq (%%rax)\n");
            } else {
                // Increment var: a++;
                printf("    incq %%rax\n");
            }
            break;
            
        case DECREMENT:
            if (operation == POINTER_DEREF) {
                // Decrement data at memory location: (*a)--;
                printf("    decq (%%rax)\n");
            } else {
                // Decrement var: a--;
                printf("    decq %%rax\n");
            }
            break;
            
        case LEFT_SHIFT:
            if (isdigit(right_value[0])) {
                // Left shift by constant: a <<= 3;
                printf("    shlq $%s, %%rax\n", right_value);
            } else {
                // Left shift by variable: a <<= b;
                printf("    shlq %%rbx, %%rax\n");
            }
            break;
            
        case ADD:
            if (isdigit(right_value[0])) {
                // Add constant: a += 15;
                printf("    addq $%s, %%rax\n", right_value);
            } else {
                // Add variable: a += b;
                printf("    addq %%rbx, %%rax\n");
            }
            break;
            
        case SUBTRACT:
            // Subtract constant: a -= 15;
            printf("    subq $%s, %%rax\n", right_value);
            break;
            
        default:
            printf("    # Unsupported operation\n");
    }
    
    sp = 0;
    return 0;
}
