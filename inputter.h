#include "stdio.h"
#include "./conio.h"
#include "string.h"

#define MAX_INT_SLOTS 8

#define NUMB_START 48
#define NUMB_END 57

#define USABLE_START 32
#define USABLE_END 126

#define ESC_KEY 27
#define ARROW_RIGHT 67
#define ARROW_LEFT 68
#define ARROW_UP 65
#define ARROW_DOWN 66

#define SQBR_LEFT 91

#define ENTER_KEY 10
#define MINUS_KEY 45
#define BACKSPACE_KEY 127

typedef enum InputRetCode
{
    Success = 0,
    Cancel = 1
};

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

// NOT YET READY
prompt_string(char message[], int size, char target[])
{
    printf("%s", message);
    int index = 0;
    int cursor = 0;
    int done = 0;
    int base_x, base_y;
    wherexy(&base_x, &base_y);
    while (!done)
    {
        char hit = getch();
        switch (hit)
        {
        case ESC_KEY:
            if (kbhit() == 0)
                return Cancel;
            else if (getch() == SQBR_LEFT)
            {
                // extended
                char special = getch();
                switch (special)
                {
                case ARROW_LEFT:
                    if (cursor > 0)
                    {
                        cursor--;
                        gotoxy(base_x + cursor, base_y);
                    }
                    break;
                case ARROW_RIGHT:
                    if (cursor < index)
                    {
                        cursor++;
                        gotoxy(base_x + cursor, base_y);
                    }
                    break;
                }
            }
            break;
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
                if (cursor > 0)
                {
                    cursor--;
                    gotoxy(base_x + cursor, base_y);
                }
            }
            break;
        case ENTER_KEY:
            target[index] = '\0';
            return;
            break;
        }
    }
}