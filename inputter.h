#include "stdio.h"
#include "./conio.h"
#include "string.h"

#define MAX_INT_SLOTS 8

#define NUMB_START 48
#define NUMB_END 57

#define USABLE_START 32
#define USABLE_END 126

#define ENTER_KEY 10
#define MINUS_KEY 45
#define BACKSPACE_KEY 127

int prompt_int(char *message)
{
    printf("%s", message);
    char buffer[MAX_INT_SLOTS];
    int index = 0;
    int done = 0;
    while (!done)
    {
        char hit = getch();
        switch (hit)
        {
        case NUMB_START ... NUMB_END:
            if (index < MAX_INT_SLOTS)
            {
                printf("%c", hit);
                buffer[index] = hit;
                index++;
            }
            break;
        case BACKSPACE_KEY:
            if (index > 0)
            {
                printf("\b ");
                gotox(wherex() - 1);
                buffer[index] = 0;
                index--;
            }
            break;
        case ENTER_KEY:
            return atoi(&buffer[0]);
            break;
            // case MINUS_KEY:
            //     if(index == 0){
            //         buffer[index] = '-';
            //         index++;
            //     }
        }
    }
}

prompt_string(char message[], int size, char target[])
{
    printf("%s", message);
    int index = 0;
    int done = 0;
    while (!done)
    {
        char hit = getch();
        switch (hit)
        {
        case USABLE_START ... USABLE_END:
            if (index < size - 1)
            {
                printf("%c", hit);
                target[index] = hit;
                index++;
            }
            break;
        case BACKSPACE_KEY:
            if (index > 0)
            {
                printf("\b ");
                gotox(wherex() - 1);
                target[index] = 0;
                index--;
            }
            break;
        case ENTER_KEY:
            target[index] = '\0';
            return;
            break;
        }
    }
}