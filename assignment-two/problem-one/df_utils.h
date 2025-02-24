//
// Andrew Ma
// alm8304
// February 24, 2025
// Homework 2, Problem 1


#ifndef DF_UTILS_H
#define DF_UTILS_H


#endif //DF_UTILS_H
#define MAX_SIZE 10


//create dataframe struct type
typedef struct dataframe {
   char col_names[MAX_SIZE][50]; //names of columns, max length 50 char
   int valid_rows; //num rows in the dataframe
   int valid_cols; //num cols in the dataframe
   double data[MAX_SIZE][MAX_SIZE]; //data array with max size
} df;


//create dataframe from input data frame
df init_df(int num_rows, int num_cols, char col_names[MAX_SIZE][50], double data[num_rows][num_cols]) {
   df df_temp;
   df_temp.valid_rows=num_rows;
   df_temp.valid_cols=num_cols;
   for (int i = 0; i < num_cols; i++) {
       strcpy(df_temp.col_names[i], col_names[i]);
   }
   for (int i = 0; i < num_rows; i++) {
       for (int j = 0; j < num_cols; j++) {
           df_temp.data[i][j] = data[i][j];
       }
   }


   return df_temp;
}
//calculate average of an input col
double calc_col_average(char use_col_name[50], df input_df) {
   for (int i = 0; i < input_df.valid_cols; i++) {
    if (strcmp(input_df.col_names[i], use_col_name) == 0) {
        double sum = 0;
        for (int j = 0; j < input_df.valid_rows; j++) {
            sum += input_df.data[j][i];
        }
        return sum / input_df.valid_rows;
    }
   }
   return 0;
}


//mostly same as calc_col_avg
double calc_col_max(char use_col_name[50], df input_df) {
   for (int i = 0; i < input_df.valid_cols; i++) {
    if (strcmp(input_df.col_names[i], use_col_name) == 0) {
        double max_val = input_df.data[0][i];
        for (int j = 1; j < input_df.valid_rows; j++) {
            if (input_df.data[j][i] > max_val) {
                max_val = input_df.data[j][i];
            }
        }
        return max_val;
    }
   }
   return 0;
}
