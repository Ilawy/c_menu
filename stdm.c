#include "stdm.h"
#include "stdio.h"

int string_len(char string[])
{
    int i = 0;
    while (string[i] != '\0')
        i++;
    return i;
}

MErrorCode string_cat(char target[], char source[], int target_real_size)
{
    int source_size = string_len(source);
    int target_size = string_len(target);
    if (source_size > target_real_size - 1)
        return ErrSmallSize;
    for (int i = 0; i < source_size; i++)
    {
        target[target_size + i] = source[i];
    }
    return ErrNoError;
}

MErrorCode string_cpy(char target[], char source[], int target_real_size)
{
    int source_size = string_len(source);
    if (source_size > target_real_size - 1)
        return ErrSmallSize;
    int i = 0;
    while (source[i] != '\0')
    {
        target[i] = source[i];
        i++;
    }
    return ErrNoError;
}

void string_upper(char string[])
{
    int i = 0;
    while (string[i] != '\0')
    {
        char c = string[i];
        if (c >= 97 && c <= 122)
            string[i] = c - 32;
        i++;
    }
}

void string_lower(char string[])
{
    int i = 0;
    while (string[i] != '\0')
    {
        char c = string[i];
        if (c >= 65 && c <= 90)
            string[i] = c + 32;
        i++;
    }
}

int string_cmp(char a[], char b[])
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
        {
            return a[i] > b[i] ? 1 : -1;
        }
        i++;
    }
    return a[i] > b[i] ? 1 : -1;
}