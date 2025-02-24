#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

int isPalindrome(char str[]) {
    int start = 0;
    int end = strlen(str) - 1;
    
    // Compare characters from start and end until pointers meet
    while (start < end) {
        // Skip non-alphanumeric characters from start
        while (start < end && !isalnum(str[start])) {
            start++;
        }
        
        // Skip non-alphanumeric characters from end
        while (start < end && !isalnum(str[end])) {
            end--;
        }
        
        // Compare characters (case-insensitive)
        if (tolower(str[start]) != tolower(str[end])) {
            return 0; // Not a palindrome
        }
        
        start++;
        end--;
    }
    
    return 1; // Is a palindrome
}

int main() {
    char str[MAX_LENGTH];
    
    printf("Enter a string: ");
    fgets(str, MAX_LENGTH, stdin);
    
    // Remove newline if present
    str[strcspn(str, "\n")] = 0;
    
    if (isPalindrome(str)) {
        printf("\"%s\" is a palindrome.\n", str);
    } else {
        printf("\"%s\" is not a palindrome.\n", str);
    }
    
    return 0;
}

