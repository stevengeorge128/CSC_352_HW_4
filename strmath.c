/*
 * File: strmath.c* Author: Steven George
 * Purpose: Read in two strings of unknown length consisting of solely integers and
 * perform the given operation on the strings (either addition or subtraction). Features
 * getline()
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* checkReturnValue(int val, int returnIfValue, char *message) -- Checks 
if the given int val is less than returnIfValue, erroring using 
the given message if yes. Assumes int val, int returnIfValue, and character
array message. Not returns.
*/
void checkReturnValue(int val, int returnIfValue, char *message)
{
    if (val < returnIfValue)
    {
        fprintf(stderr, "%s", message);
        exit(1);
    }
}

/* newlineToNullTerm(char *operation) -- Takes a character array, removes the trailing
newline and replaces it with the null terminator. Assumes character array pointer. No
return value.
*/
void newlineToNullTerm(char *operation)
{
    if (operation[strlen(operation) - 1] == '\n')
    {
        operation[strlen(operation) - 1] = '\0';
    }
}

/* isArrayNumeric(char *str) -- Check if an array is numeric. Returns 1 if yes, false
otherwise. Exits program with error upon receiving an empty string. Assumes char pointer
input. Returns int. 
*/
int isArrayNumeric(char *str)
{
    if (strcmp(str, "") == 0){
        fprintf(stderr, "Error: line does not contain any digits\n");
        exit(1);
    }
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

/*removeLeadingZeros(char *str) -- Removes leading zeros from character array. Assumes
character pointer input. Returns character array pointer
*/
char *removeLeadingZeros(char *str)
{
    // While first character is zero and we haven't reached the null terminator
    while (*str == '0' && *(str + 1) != '\0')
    {
        str++;
    }
    return str;
}

/* char *addLeadingZeros(char *arr, int newSize) -- Adds leading zeros to arr until 
arr matches the size of newSize. Takes character arr of string to update the the new size.
Assumes newSize is larger than arr size. Returns char array pointer. 
*/
char *addLeadingZeros(char *arr, int newSize)
{
    // Allocate memory and error check. 
    int oldArrayIndex = 0;
    char *newArr = malloc(sizeof(char) * newSize);
    if (newArr == NULL)
    {
        fprintf(stderr, "Error: Out of memory");
        exit(1);
    }
    // Calc zeros to add and return arr if none
    int zerosToAdd = newSize - strlen(arr);
    if (zerosToAdd == 0)
    {
        return arr;
    }
    // Else loop through newArr and add zeros, or switch to old array values.
    for (int i = 0; i < newSize; i++)
    {
        if (i < zerosToAdd)
        {
            newArr[i] = '0';
        }
        else
        {
            newArr[i] = arr[oldArrayIndex];
            oldArrayIndex++;
        }
    }
    return newArr;
}

/*char *subtractString(char *str1, char *str2) -- Major method for string subtraction. 
Calculates the value by iterating through the length of the longer string and conducting
subtraction on each corresponding index, starting with the rightmost, or least significant,
digit. Borrows from next digit when required. Assumes both parameters are character arrays
pointing to strings with only integer characters. Returns character array of the result
of the subtraction. 
*/
char *subtractString(char *str1, char *str2)
{
    // Establish req variables. 
    char *result;
    int size;
    char *arrA;
    char *arrB;
    int intA;
    int intB;
    int singleValResultInt;
    int borrow;
    // First we check if the result will be negative. Then we add leading zeros 
    // to the shorter array to make operations easier.
    int neg = 0;
    if (strlen(str1) < strlen(str2) || (strlen(str1) == strlen(str2) && strcmp(str1, str2) < 0))
    {
        // If neg then str 2 is larger and will decide the basis for memory allocation
        neg = 1;
        arrA = str2;
        size = strlen(arrA);
        arrB = addLeadingZeros(str1, size);
        result = malloc(sizeof(char) * (size + 1));
        if (result == NULL)
        {
            fprintf(stderr, "Error: Out of memory");
            exit(1);
        }
    }
    else 
    {
        // Else str1 is bigger and thus determines the basis for memory allocations
        arrA = str1;
        size = strlen(arrA);
        arrB = addLeadingZeros(str2, size);
        result = malloc(sizeof(char) * (size + 1));
        if (result == NULL)
        {
            fprintf(stderr, "Error: Out of memory");
            exit(1);
        }
    }
    result[size] = '\0';
    borrow = 0;

    for (int i = size - 1; i >= 0; i--)
    {
        // For each int in the size of the larger array

        intA = arrA[i] - '0';
        intB = arrB[i] - '0';


        // Adjust intA from any prior borrowing
        if (borrow == 1)
        {
            intA--;
            borrow = 0;
        }

        // Handle current borrowing if intA is less than intB
        if (intA < intB)
        {
            intA += 10; // Borrow from the next higher digit
            borrow = 1; // Set borrow for the next iteration
        }
        singleValResultInt = intA - intB; // Calc new digit
        result[i] = singleValResultInt + '0';
    }
    result = removeLeadingZeros(result);

    if (neg == 1)
    {
        // If negative result allocate more memory and add negative sign
        char *final = malloc(sizeof(char) * (strlen(result)+1));
        if (final == NULL)
        {
            fprintf(stderr, "Error: Out of memory");
            exit(1);
        }
        final[0] = '-';
        strcpy(final + 1, result);
        return final;
    }

    return result;
}

/*char *addStrings(char *str1, char *str2) -- Major method for string addition. 
Calculates the value by iterating through the length of the longer string and conducting
addition on each corresponding index, starting with the rightmost, or least significant,
digit. Carries from previous digit when required. Assumes both parameters are character arrays
pointing to strings with only integer characters. Returns character array of the result
of the addition. 
*/
char *addStrings(char *str1, char *str2)
{
    // Establish pointers
    char *result;
    int size;
    char *arrA;
    char *arrB;
    int intA;
    int intB;
    int singleValResultInt;
    // Allocate memory for result depending on larger char array size
    // Add leading zeros to shorter array to make operations easier
    if (strlen(str1) > strlen(str2))
    {
        size = strlen(str1);
        result = malloc(sizeof(char) * (size + 2));
        if (result == NULL)
        {
            fprintf(stderr, "Error: Out of memory");
            exit(1);
        }

        arrA = str1;
        arrB = addLeadingZeros(str2, size);
    }
    else
    {
        size = strlen(str2);
        result = malloc(sizeof(char) * (size + 2));
        if (result == NULL)
        {
            fprintf(stderr, "Error: Out of memory");
            exit(1);
        }

        arrA = str2;
        arrB = addLeadingZeros(str1, size);
    }

    result[size+1] = '\0';
    int carry = 0;

    for (int i = size - 1; i >= 0; i--)
    {
        // For each character in string we get its int value, and calculate the sum of 
        // both values plus the result of the carry from the previous additions
        intA = arrA[i] - '0';
        intB = arrB[i] - '0';

        singleValResultInt = intA + intB + carry;
        if (singleValResultInt > 9)
        {
            singleValResultInt = singleValResultInt % 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        result[i+1] = singleValResultInt + '0';
    }


    // Incase final digit carries
    if (carry == 1)
    {
        result[0] = '1';
        return result;
    }
    return removeLeadingZeros(result+1);
}

int main()
{
    // Establish pointers 
    int errorOccurred = 0;
    char *operation = NULL;
    char *str1 = NULL;
    char *str2 = NULL;
    size_t lenOp = 0;
    size_t len1 = 0;
    size_t len2 = 0;
    int retVal;
    char *result;
    
    // Get first line an error under multiple shown conditions
    retVal = getline(&operation, &lenOp, stdin);
    newlineToNullTerm(operation);
    if ((strcmp(operation, "add") != 0) && (strcmp(operation, "sub") != 0))
    {
        errorOccurred = 1;
        fprintf(stderr, "Error: 1st line not equal to 'add' or 'sub'\n");
        return errorOccurred;
    }

    // Get next line
    // Check if end of line or error reading line
    // Convert newline character to null terminator
    // Ensure newline is numeric
    retVal = getline(&str1, &len1, stdin);
    checkReturnValue(retVal, 1, "Error: not enough inputs\n");
    newlineToNullTerm(str1);
    if (isArrayNumeric(str1) == 0)
    {
        errorOccurred = 1;
        fprintf(stderr, "Error: Non-integer characters in input\n");
        return errorOccurred;
    }

    // Repeat for second string int
    retVal = getline(&str2, &len2, stdin);
    checkReturnValue(retVal, 1, "Error: not enough inputs\n");
    newlineToNullTerm(str2);
    if (isArrayNumeric(str2) == 0)
    {
        errorOccurred = 1;
        fprintf(stderr, "Error: Non-integer characters in input\n");
        return errorOccurred;
    }

    str1 = removeLeadingZeros(str1);
    str2 = removeLeadingZeros(str2);

    // If both strings zero, return zero. 
    if ((strcmp(str1, "0") == 0) && (strcmp(str2, "0") == 0))
    {
        printf("%s\n", str1);
        return errorOccurred;
    }

    // If second string zero, return first string
    if (strcmp(str2, "0") == 0)
    {
        printf("%s\n", str1);
        return errorOccurred;
    }

    // If first string zero, return second string, checking for subtraction for neg sign
    if (strcmp(str1, "0") == 0)
    {
        if (strcmp(operation, "sub") == 0)
        {
            printf("-%s\n", str2);
            return errorOccurred;
        }
        printf("%s\n", str2);
        return errorOccurred;
    }

    // Adding case
    if (strcmp(operation, "add") == 0)
    {
        result = addStrings(str1, str2);
        // removeLeadingZeros(result);
        printf("%s\n", result);
    }
    else
    { // Subtracting case
        result = subtractString(str1, str2);
        printf("%s\n", result);
    }

    return errorOccurred;
}