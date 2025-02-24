#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "df_utils.h"


void main(void) {
   //set row num
   int r = 5;
   //set col num
   int c = 7;
   //initialize array for data
   double my_data[r][c];


   //just add some values for the data
   for (int i = 0; i < r; i++) {
       for (int j = 0; j < c; j++) {
           my_data[i][j] = ((1+i*i)+2*(1+i*j)+(1+j*j)) * (0.77 * (i+j % 2) );
       }
   }


   //create an array of col names
   char col_labels[7][50] = {"temp","pressure","volume","time","density","velocity","angle"};
   //initialize a dataframe
   df test_df = init_df(r, c, col_labels, my_data);


   double average = calc_col_average("volume", test_df);
   double max_val = calc_col_max("volume", test_df);
   double max_height = calc_col_max("height", test_df); //this should exit with error message
   printf("Average volume is %.3f\n",average);
   printf("Max volume is %.3f\n",max_val);
}

