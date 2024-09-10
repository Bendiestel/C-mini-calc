#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>
// gcd code was taken from chatGPT
// Explaination of algorithm: 
// Base Case: If b is 0, return a as the GCD.
//Recursive Step: Otherwise, call gcd again with b and the remainder of a divided by b (i.e., a % b).
//This process repeats until b becomes zero, at which point a is the GCD
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
// Function to check if two strings are anagrams of each other
int areAnagrams(const char *str1, const char *str2) {
    int count[256] = {0};
    int i;
    for (i = 0; str1[i] && str2[i]; i++) {
        count[(unsigned char)str1[i]]++;
        count[(unsigned char)str2[i]]--;
    }
    return str1[i] == '\0' && str2[i] == '\0';
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: No operation provided\n");
        return 1;
    }
    
    char *op = argv[1];
    char *endptr;
    
    if (strcmp(op, "+") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Error: Addition requires exactly two arguments\n");
            return 3;
        }
         // Convert string arguments to long integers and check for conversion errors
        errno = 0;
        long num1 = strtol(argv[2], &endptr, 10);
        if (*endptr != '\0' || errno != 0) {
            fprintf(stderr, "Error: Operands must be of the correct type\n");
            return 4;
        }
        long num2 = strtol(argv[3], &endptr, 10);
        if (*endptr != '\0' || errno != 0) {
            fprintf(stderr, "Error: Operands must be of the correct type\n");
            return 4;
        }
        printf("%ld\n", num1 + num2);
    // GCD operation
    } else if (strcmp(op, "gcd") == 0) {
        if (argc < 4) {
            fprintf(stderr, "Error: GCD requires at least two arguments\n");
            return 3;
        }
        int result = 0;
        for (int i = 2; i < argc; i++) {
            errno = 0;
            long num = strtol(argv[i], &endptr, 10);
            if (*endptr != '\0' || errno != 0) {
                fprintf(stderr, "Error: Operands must be of the correct type\n");
                return 4;
            }
            if (num <= 0) {
                fprintf(stderr, "Error: GCD operands must be greater than zero\n");
                return 7;
            }
            result = i == 2 ? num : gcd(result, num);
        }
        printf("%d\n", result);
     // Square root operation
    } else if (strcmp(op, "sqrt") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Error: Square root requires exactly one argument\n");
            return 3;
        }
        errno = 0;
        double num = strtod(argv[2], &endptr); // Convert string to double
        if (*endptr != '\0' || errno != 0) {
            fprintf(stderr, "Error: Operands must be of the correct type\n");
            return 4;
        }
        if (num < 0) {
            fprintf(stderr, "Error: Square root input must be nonnegative\n");
            return 5;
        }
        printf("%.2f\n", sqrt(num));
    // Anagram operation
    } else if (strcmp(op, "anagram") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Error: Anagram requires exactly two arguments\n");
            return 3;
        }
        // Ensure both input strings contain only lowercase letters
        for (int i = 0; argv[2][i]; i++) {
            if (!islower((unsigned char)argv[2][i])) {
                fprintf(stderr, "Error: Inputs must consist only of lowercase letters\n");
                return 6;
            }
        }
        for (int i = 0; argv[3][i]; i++) {
            if (!islower((unsigned char)argv[3][i])) {
                fprintf(stderr, "Error: Inputs must consist only of lowercase letters\n");
                return 6;
            }
        }
        // Unknown operation
        printf("%s\n", areAnagrams(argv[2], argv[3]) ? "true" : "false");
    } else {
        fprintf(stderr, "Error: Unknown operation '%s'\n", op);
        return 2;
    }

    return 0;
}

