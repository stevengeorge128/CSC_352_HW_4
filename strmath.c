/*
 * File: strmath.c* Author: Steven George
 * Purpose: Read in two strings of unknown length consisting of solely integers
 * perform the given operation on the strings (either addition or subtraction)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void checkReturnValue(int val, int returnIfValue, char *message)
{
    if (val < returnIfValue)
    {
        fprintf(stderr, "%s", message);
        exit(1);
    }
}

void newlineToNullTerm(char *operation)
{
    if (operation[strlen(operation) - 1] == '\n')
    {
        operation[strlen(operation) - 1] = '\0';
    }
}

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

char *removeLeadingZeros(char *str)
{
    // int len = strlen(str);
    // int breakPoint = -1;
    // for (int i = 0; i < len; i ++){
    //     if (str[i] != '0'){
    //         return str[i];
    //     }
    // }
    // While first character is zero and we haven't reached the null terminator
    while (*str == '0' && *(str + 1) != '\0')
    {
        str++;
    }
    return str;
}

char *addLeadingZeros(char *arr, int newSize)
{
    // printf("----------\n inside addLeadingZeros");
    // printf("new size is %d\n", newSize);
    // printf("arr len is %lu\n" , strlen(arr));
    // printf("arr is %s\n", arr);
    int oldArrayIndex = 0;
    char *newArr = malloc(sizeof(char) * newSize);
    if (newArr == NULL)
    {
        fprintf(stderr, "Error: Out of memory");
        exit(1);
    }
    int zerosToAdd = newSize - strlen(arr);
    if (zerosToAdd == 0)
    {
        return arr;
    }
    // printf("zerosToAdd is  %d\n", zerosToAdd);
    for (int i = 0; i < newSize; i++)
    {
        //  printf("newArr is %s\n", newArr);
        //  printf("i is %d\n", i);
        if (i < zerosToAdd)
        {
            newArr[i] = '0';
        }
        else
        {
            //  printf("Inside the else statement where oldArrayIndex is %d\n", oldArrayIndex);
            newArr[i] = arr[oldArrayIndex];
            oldArrayIndex++;
        }
        // printf("here\n");
    }
    // printf("Leaving addLeadingZeros\n ----------\n ");

    return newArr;
}

char *subtractString(char *str1, char *str2)
{

    char *result;
    int size;
    char *arrA;
    char *arrB;
    char charA;
    char charB;
    int intA;
    int intB;
    int singleValResultInt;
    int borrow;
    // First we check if the result will be negative
    int neg = 0;
    if (strlen(str1) < strlen(str2) || (strlen(str1) == strlen(str2) && strcmp(str1, str2) < 0))
    {
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

    // printf("arrA is %s\n", arrA);
    // printf("arrB is %s\n", arrB);
    for (int i = size - 1; i >= 0; i--)
    {
        // printf("Looping --------------------\n");
        // printf("arrA is %s\n", arrA);
        // printf("arrB is %s\n", arrB);
        // printf("i is %d\n", i);
        charA = arrA[i];
        charB = arrB[i];
        intA = charA - '0';
        intB = charB - '0';
        // if (borrow == 1)
        // {
        //     intA--;
        // }
        // printf("before if intA is %d\n", intA);
        // if (intA < (intB + borrow))
        // {
        //     // intA += 10;
        //     // borrow = 1;
        //     intA += 10;                                // Borrow from the next digit
        //     singleValResultInt = intA - intB - borrow; // Perform the subtraction
        //     borrow = 1;                                // Set borrow for the next iteration
        // }
        // else
        // {
        //     if (borrow == 1){
        //         intA --;
        //     }
        //     singleValResultInt = intA - intB - borrow;
        //     borrow = 0; // No need to borrow
        // }
        // if (intA < intB)
        // {
        //     intA += 10;
        //     borrow = 1;
        //     singleValResultInt = intA - intB;
        // }
        // else
        // {
        //     if (borrow == 1)
        //     {
        //         printf("intA decremented by 1");
        //         intA--;
        //     }
        //     if (intA < intB)
        //     {
        //         intA += 10;
        //         borrow = 1;
        //         singleValResultInt = intA - intB;
        //     }
        //     else
        //     {
        //         borrow = 0;
        //     }
        //     singleValResultInt = intA - intB;
        // }

                // Adjust intA for any prior borrowing
        if (borrow == 1)
        {
            intA--;  // Account for the previous borrow
            borrow = 0;
        }

        // Handle current borrowing if intA is less than intB
        if (intA < intB)
        {
            intA += 10; // Borrow from the next higher digit
            borrow = 1; // Set borrow for the next iteration
        }
        // printf("after if intA is %d\n", intA);
        // printf("intB is %d\n", intB);
        // printf("borrow is %d\n", borrow);

        // // borrow = 0;
        singleValResultInt = intA - intB;
        // printf("singleValResultInt is %d\n", singleValResultInt);
        // printf("singleValResultInt  + '0' is %c\n", singleValResultInt + '0');

        result[i] = singleValResultInt + '0';
        // printf("result[i] is %c\n", result[i]);
    }

    result = removeLeadingZeros(result);

    if (neg == 1)
    {

        char *final = malloc(sizeof(char) * strlen(result));
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

char *addStrings(char *str1, char *str2)
{

    char *result;
    int size;
    char *arrA;
    char *arrB;
    char charA;
    char charB;
    int intA;
    int intB;
    int singleValResultInt;
    //  Allocate memory for result depending on large char array size
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
    result[size] = '\0';
    int carry = 0;

    // printf("arrA is %s\n", arrA);
    // printf("arrB is %s\n", arrB);

    for (int i = size - 1; i >= 0; i--)
    {

        charA = arrA[i];
        charB = arrB[i];
        intA = charA - '0';
        intB = charB - '0';

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
        result[i] = singleValResultInt + '0';
    }



    if (carry == 1)
    {
        result[0] = '1';
        return result;
    }
    return removeLeadingZeros(result);
}

int main()
{
    int errorOccurred = 0;
    char *operation = NULL;
    char *str1 = NULL;
    char *str2 = NULL;
    size_t lenOp = 0;
    size_t len1 = 0;
    size_t len2 = 0;
    int retVal;
    char *result;

    retVal = getline(&operation, &lenOp, stdin);
    newlineToNullTerm(operation);

    if ((strcmp(operation, "add") != 0) && (strcmp(operation, "sub") != 0))
    {
        errorOccurred = 1;
        fprintf(stderr, "Error: 1st line not equal to 'add' or 'sub'\n");
        return errorOccurred;
    }
    // checkReturnValue(retVal, 1,"Error: 1st line not equal to 'add' or 'sub'\n" );

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
    // printf("After removing leading zeros str1 is %s \n", str1);
    // printf("After removing leading zeros str2 is %s \n", str2);

    // If first string zero, return second, covering negative case
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





    if (strcmp(operation, "add") == 0)
    {
        result = addStrings(str1, str2);
        // removeLeadingZeros(result);
        printf("%s\n", result);
    }
    else
    {
        result = subtractString(str1, str2);
        // removeLeadingZeros(result);
        printf("%s\n", result);
    }

    return errorOccurred;
}