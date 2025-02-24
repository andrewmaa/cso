#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Andrew Ma
//alm8304
//February 10, 2025
//Homework 1, Problem 3

//function declarations
int check_password_fast(char stored_password[], char guess_password2[]);
int check_password_slow(char stored_password[], char guess_password2[]);


//check password fast, exit at first incorrect char
int check_password_fast(char stored_password[], char guess_password2[]) {
   //get size of stored password
   size_t len_sp = strlen(stored_password);
   //get size of guess password
   size_t len_guess = strlen(guess_password2);
   //exit if lengths do not match
   if (len_guess != len_sp) {
       //can print, but annoying if running many times
       //printf("Incorrect Password\n");
       return 0;
   }

   //if we didn't exit for incorrect password length then
   //we'd want to get the length of the shorter password
   //to use in our loop iteration
   int min_len = (len_sp > len_guess) ? len_sp : len_guess;
   //iterate over all chars in password
   for (int i = 0; i < min_len; i++) {
       //check if each corresponding password matches
       if (stored_password[i] != guess_password2[i]) {
           //printf("Incorrect Password\n");
           //exit at first wrong char
           return 0;
       }
   }
   //if all char matched, and we didn't exit earlier
   //printf("Password is Correct\n");
   return 1;

}

int check_password_slow(char stored_password[], char guess_password2[]) {
   //get size of stored password
   size_t len_sp = strlen(stored_password);
   //get size of guess password
   size_t len_guess = strlen(guess_password2);
   
   //create new array for password buffer
   char password_buffer[len_sp];
   
   //if input password is shorter, copy first len_guess chars and pad with \n
   if (len_guess < len_sp) {
       strncpy(password_buffer, guess_password2, len_guess);
       for (int i = len_guess; i < len_sp; i++) {
           password_buffer[i] = '\n';
       }
   } else {
       //otherwise copy first len_sp chars of input password
       strncpy(password_buffer, guess_password2, len_sp);
   }
   
   //compare buffers and return 1 if equal, 0 if not equal
   if (strcmp(password_buffer, stored_password) == 0) {
       return 1;
   }
   return 0;
}

int main() {

   //stored password
   char my_pass[]="pASSw0rD";
   //compare runtime 3 guesses
   char guess_pass_1[] = "PASSword1"; //first char wrong
   char guess_pass_2[] = "pASSW0rd"; //only last char wrong
   char guess_pass_3[] = "pASSw0rD"; //correct password

   //declare timer vars
   clock_t start, end;
   //decide how many times to run to get sum over many trials
   int loop_iter = 100000000;
   printf("runtimes for check_password_fast:\n");

   //start timer
   start = clock();
   //run many times
   for (int i = 0; i < loop_iter; i++) {
       check_password_fast(my_pass, guess_pass_1);
   }
   //end timer
   end = clock();
   double time_to_run1 = (double)(end - start) / CLOCKS_PER_SEC;

   start = clock();
   for (int i = 0; i < loop_iter; i++) {
       check_password_fast(my_pass, guess_pass_2);
   }
   end = clock();
   double time_to_run2 = (double)(end - start) / CLOCKS_PER_SEC;

   start = clock();
   for (int i = 0; i < loop_iter; i++) {
       check_password_fast(my_pass, guess_pass_3);
   }
   end = clock();
   double time_to_run3 = (double)(end - start) / CLOCKS_PER_SEC;


   printf("Time to run 1: %f\n", time_to_run1);
   printf("Time to run 2: %f\n", time_to_run2);
   printf("Time to run 3: %f\n", time_to_run3);

   printf("runtimes for check_password_slow:\n");

   start = clock();
   for (int i = 0; i < loop_iter; i++) {
       check_password_slow(my_pass, guess_pass_1);
   }
   end = clock();
   double time_to_run1_slow = (double)(end - start) / CLOCKS_PER_SEC;

   start = clock();
   for (int i = 0; i < loop_iter; i++) {
       check_password_slow(my_pass, guess_pass_2);
   }
   end = clock();
   double time_to_run2_slow = (double)(end - start) / CLOCKS_PER_SEC;

   start = clock();
   for (int i = 0; i < loop_iter; i++) {
       check_password_slow(my_pass, guess_pass_3);
   }
   end = clock();
   double time_to_run3_slow = (double)(end - start) / CLOCKS_PER_SEC;


   printf("Time to run 1: %f\n", time_to_run1_slow);
   printf("Time to run 2: %f\n", time_to_run2_slow);
   printf("Time to run 3: %f\n", time_to_run3_slow);


}

//Output:
//=thread-selected,id="1"
//runtimes for check_password_fast:
//Time to run 1: 0.540506
//Time to run 2: 1.262080
//Time to run 3: 1.770432
//runtimes for check_password_slow:
//Time to run 1: 1.635876
//Time to run 2: 1.640655
//Time to run 3: 1.634747