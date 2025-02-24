#include <stdio.h>
#include <math.h>
#define ARRAY_SIZE 20

//Andrew Ma
//alm8304
//February 10, 2025
//Homework 1, Problem 4

//global array to hold result
int fib_arr[ARRAY_SIZE];

//global array to store counts for
//counts[0] number loop iters
//counts[1] number flops
//counts[2] number reads
//counts[3] number writes
//counts[4] number calls to ext func
int counts[5];

void print_fib_arr() {
   for (int i = 0; i < ARRAY_SIZE; i++) {
       printf("%d  ", fib_arr[i]);
   }
   printf("\n");
}

void print_counts() {
   printf("Num iter: %d, Num flop: %d, Num reads: %d, Num writes: %d, Num ext func calls: %d\n",
          counts[0],counts[1],counts[2],counts[3],counts[4]);
}

void clear_vars() {
   for (int i = 0; i < ARRAY_SIZE; i++) {
       fib_arr[i] = 0;
   }
   //initialize first 2 vals
   fib_arr[0] = 0;
   fib_arr[1] = 1;
   for (int i = 0; i < 5; i++) {
       counts[i] = 0;
   }
}

void fib1() {
   //calc next values
   for (int i = 2; i < ARRAY_SIZE; i++) {
       counts[0]++; // loop iteration
       counts[2] += 2; // read fib_arr[i-1] and fib_arr[i-2]
       counts[1]++; // one addition
       counts[3]++; // write to fib_arr[i]
       fib_arr[i] = fib_arr[i - 1] + fib_arr[i - 2];
   }
}

void fib2() {
   for (int i = 2; i < ARRAY_SIZE; i+=2) {
       counts[0]++; // loop iteration
       counts[2] += 2; // read fib_arr[i-1] and fib_arr[i-2]
       int fib_n_1 = fib_arr[i - 1];
       counts[1]++; // addition for fib_arr[i]
       fib_arr[i] = fib_n_1 + fib_arr[i - 2];
       counts[3]++; // write to fib_arr[i]
       
       counts[1]++; // addition for fib_arr[i+1]
       counts[3]++; // write to fib_arr[i+1]
       fib_arr[i+1] = fib_arr[i] + fib_n_1;
   }
}

void fib3() {
   float golden_ratio = 1.618;
   fib_arr[2] = 1;
   counts[3]++; // initial write

   for (int i = 3; i < ARRAY_SIZE; i++) {
       counts[0]++; // loop iteration
       counts[2]++; // read fib_arr[i-1]
       counts[1]++; // multiplication by golden_ratio
       counts[3]++; // write to fib_arr[i]
       counts[4]++; // call to round()
       fib_arr[i] = (int)round(fib_arr[i - 1] * golden_ratio);
   }
}

void fib4() {
   counts[4]++; // sqrt(5)
   float sqrt_of_5 = sqrt(5);

   counts[1]++; // division for recip_sqrt5
   float recip_sqrt5 = 1.0 / sqrt_of_5;

   counts[1] += 2; // addition and division for a
   float a = (1+sqrt_of_5)/2;

   counts[1] += 2; // subtraction and division for b
   float b = (1-sqrt_of_5)/2;

   for (int i = 2; i < ARRAY_SIZE; i++) {
       counts[0]++; // loop iteration
       counts[4] += 2; // two calls to pow()
       counts[1] += 2; // subtraction and multiplication
       counts[3]++; // write to fib_arr[i]
       fib_arr[i] = recip_sqrt5 * (pow(a, i) - pow(b, i));
   }
}

void main() {
   clear_vars();
   printf("run fib1\n");
   fib1();
   print_fib_arr();
   print_counts();

   clear_vars();
   printf("run fib2\n");
   fib2();
   print_fib_arr();
   print_counts();

   clear_vars();
   printf("run fib3\n");
   fib3();
   print_fib_arr();
   print_counts();

   clear_vars();
   printf("run fib4\n");
   fib4();
   print_fib_arr();
   print_counts();

}

//Output:
//run fib1
//0  1  1  2  3  5  8  13  21  34  55  89  144  233  377  610  987  1597  2584  4181  
//Num iter: 18, Num flop: 18, Num reads: 36, Num writes: 18, Num ext func calls: 0
//run fib2
//0  1  1  2  3  5  8  13  21  34  55  89  144  233  377  610  987  1597  2584  4181  
//Num iter: 9, Num flop: 18, Num reads: 18, Num writes: 18, Num ext func calls: 0
//run fib3
//0  1  1  2  3  5  8  13  21  34  55  89  144  233  377  610  987  1597  2584  4181  
//Num iter: 17, Num flop: 17, Num reads: 17, Num writes: 18, Num ext func calls: 17
//run fib4
//0  1  1  2  3  5  8  13  21  34  55  89  144  233  377  610  987  1597  2584  4181  
//Num iter: 18, Num flop: 41, Num reads: 0, Num writes: 18, Num ext func calls: 37
