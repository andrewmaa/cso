// Andrew Ma
// alm8304
// 03/09/2025
// Homework 3, Problem 1


#ifndef COLOR_UTIL_H
#define COLOR_UTIL_H
#include <stdio.h>
#include <stdlib.h>


#endif //COLOR_UTIL_H


//create color node datatype
//alias type to name color_node
typedef struct color_node
{
   long int color;
   struct color_node *next;
} color_node;


//an array to store the rgb components separately
int rgb_array[3];


// Function to create a new color node
color_node *make_color(long int value){


   // Allocate memory
   color_node *new_color =
     (color_node *)malloc(sizeof(color_node));


   // Set color value
   new_color->color = value;


   // Initialize next to NULL
   new_color->next = NULL;


   // Return the new node
   return new_color;
}


//create a color wheel with just primary colors
color_node *init_with_primary() {
   color_node *red =  make_color(0x00FF0000);
   color_node *green = make_color(0x0000FF00);
   color_node *blue = make_color(0x000000FF);


   red->next = green;
   green->next = blue;
   blue->next = red;
   return red;
}


//helper function to separate bytes of int value
void rgb_int_to_array(color_node *c) {
   int c_int_val = c->color;
   //get only red bytes
   int c_r = (c_int_val & 0xFF0000) >> 16;
   //get only green bytes
   int c_g = (c_int_val & 0x00FF00) >> 8;
   //get only blue bytes
   int c_b = (c_int_val & 0x0000FF);
   //put into array
   rgb_array[0] = c_r;
   rgb_array[1] = c_g;
   rgb_array[2] = c_b;
}


//print out all nodes in wheel
void print_wheel(color_node *c) {
   color_node *start = c;
   do {
       printf("Color: %06x\n", c->color);
       c = c->next;
   } while (c != start);
}

void mix_with_neighbor(color_node *base) {
   //get rgb values of base color
   rgb_int_to_array(base);
   int r = rgb_array[0];
   int g = rgb_array[1];
   int b = rgb_array[2];
   //get rgb values of next color
   rgb_int_to_array(base->next);
   int r_neighbor = rgb_array[0];
   int g_neighbor = rgb_array[1];
   int b_neighbor = rgb_array[2];
   //calculate average of rgb values
   int avg_r = (r + r_neighbor) / 2;
   int avg_g = (g + g_neighbor) / 2;
   int avg_b = (b + b_neighbor) / 2;
   //create new color
   long int mixed_color = (avg_r << 16) | (avg_g << 8) | avg_b;
   //create new color node
   color_node *new_color = make_color(mixed_color);
   //update next pointer
   color_node *old_next = base->next;
   base->next = new_color;
   new_color->next = old_next;
} 