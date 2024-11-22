#include "stdio.h"
#include "inputter.h"

int main()
{
    char buffer[100];
    prompt_string("Enter a string: ", 100, buffer);
    printf("You entered: %s\n", buffer);

    return 0;
}