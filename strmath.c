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

char *addStrings(char *str1, char *str2)
{
    char *result;
    if (strlen(str1) > strlen(str2))
    {
        result = malloc(strlen(str1) + 1);
    }
    else
    {
        result = malloc(strlen(str2) + 1);
    }
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

    retVal = getline(&operation, &lenOp, stdin);
    newlineToNullTerm(operation);

    if ((strcmp(operation, "add") != 0) && (strcmp(operation, "sub") != 0))
    {
        errorOccurred = 1;
        fprintf(stderr, "Error: 1st line not equal to 'add' or 'sub'");
        return errorOccurred;
    }
    // checkReturnValue(retVal, 1,"Error: 1st line not equal to 'add' or 'sub'" );

    // Get next line
    // Check if end of line or error reading line
    // Convert newline character to null terminator
    // Ensure newline is numeric
    retVal = getline(&str1, &len1, stdin);
    checkReturnValue(retVal, 1, "Error: not enough inputs");
    newlineToNullTerm(str1);
    if (isArrayNumeric(str1) == 0)
    {
        errorOccurred = 1;
        fprintf(stderr, "Error: Non-integer characters in input");
        return errorOccurred;
    }

    // Repeat for second string int
    retVal = getline(&str2, &len2, stdin);
    checkReturnValue(retVal, 1, "Error: not enough inputs");
    newlineToNullTerm(str2);
    if (isArrayNumeric(str1) == 0)
    {
        errorOccurred = 1;
        fprintf(stderr, "Error: Non-integer characters in input");
        return errorOccurred;
    }

    str1 = removeLeadingZeros(str1);
    str2 = removeLeadingZeros(str2);

    if (strcmp(operation, "add") == 0)
    {
        addStrings(str1, str2);
    }

    return errorOccurred;
}
