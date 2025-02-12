// This is a C Program by Achutha Aswin Naick 
// to implement Booth's Division algorithm without using *, / operators.

#include <stdio.h>  // Standard I/O library for printf and scanf
#include <stdlib.h> // Standard library for general functions
#include <limits.h> // Library for integer limits

// Function to determine the number of bits needed to represent a number
int getBitLength(int num) {
    if (num == 0) return 1; // If number is zero, at least one bit is required
    if (num < 0) num = -num; // Convert negative number to positive for bit calculation
    int bitLength = 0;
    while (num > 0) {
        bitLength++; // Increment bit count
        num >>= 1; // Right shift number to process the next bit
    }
    return bitLength;
}

// Function to print a number in binary representation up to a given number of bits

void printBinary(int n, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (n >> i) & 1); // Extract and print each bit
    }
}

// Function implementing Booth's Division Algorithm
void boothDivider(int divisor, int dividend) {
    if (divisor == 0) { // Check for division by zero
        printf("Error: Division by zero!\n");
        return;
    }

    int original_dividend = dividend; // Store the original dividend for reference
    int original_divisor = divisor;   // Store the original divisor for reference
    int sign = 1; // Variable to keep track of the result's sign
    
    // Convert both numbers to positive if negative and adjust sign
    if (dividend < 0) {
        sign = -sign; // Flip sign if dividend is negative
        dividend = -dividend;
    }
    if (divisor < 0) {
        sign = -sign; // Flip sign if divisor is negative
        divisor = -divisor;
    }

    int numBits = getBitLength(dividend); // Get the bit length of the dividend
    int quotient = 0; // Initialize quotient to 0
    int remainders = 0; // Initialize remainder to 0

    // Iterate through each bit of the dividend
    for (int i = numBits - 1; i >= 0; i--) {
        remainders = (remainders << 1) | ((dividend >> i) & 1); // Shift left and add next bit of dividend
        int msbA = (remainders >> (numBits - 1)) & 1; // Extract MSB of accumulator
        int msbM = (divisor >> (numBits - 1)) & 1; // Extract MSB of divisor

        if (msbA == msbM) { // Check if both MSBs are same
            remainders -= divisor; // Perform subtraction if MSBs match
        } else {
            remainders += divisor; // Perform addition if MSBs do not match
        }

        int newMsbA = (remainders >> (numBits - 1)) & 1; // Extract new MSB after operation

        if (msbA != newMsbA) { // If MSB changes, revert operation
            if (msbA == 0) {
                remainders += divisor; // Re-add divisor to correct error
            } else {
                remainders -= divisor; // Re-subtract divisor to correct error
            }
        } else {
            quotient |= (1 << i); // Set the corresponding bit in quotient
        }
    }

    if (sign == -1) { // If original result was negative, negate quotient
        quotient = -quotient;
    }

    // Print the results
    printf("Quotient: %d\n", quotient);
    printf("Remainder: %d\n", remainders);
}

int main() {
    int M, Q;
    // Take user input for divisor and dividend
    printf("Enter the divisor (M): ");
    scanf("%d", &M);
    printf("Enter the dividend (Q): ");
    scanf("%d", &Q);
    
    boothDivider(M, Q); // Call the Booth's division function
    
    return 0; 
}
