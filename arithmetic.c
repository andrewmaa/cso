/*
Implement a function that accepts a function pointer for basic arithmetic operations.

Swap two pointers using a pointer to a pointer.

Allocate memory dynamically for an array and free it afterward.*/

#include <stdio.h>
#include <stdlib.h>

void arithmetic(int (*operation)(int, int)) {
    int a = 10;
    int b = 20;
    int result = operation(a, b);
    printf("Result: %d\n", result);
}

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b == 0) {
        printf("Error: Division by zero\n");
        return 0;
    }
    return a / b;
}   

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void allocate_array() {
    int *array = (int *)malloc(10 * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }
    free(array);
}

int main() {
    arithmetic(add);
    arithmetic(subtract);
    arithmetic(multiply);
    arithmetic(divide);

    int a = 10;
    int b = 20;
    printf("Before swap: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("After swap: a = %d, b = %d\n", a, b);

    allocate_array();
    
    return 0;
}