
typedef enum
{
    ArrowUp,
    ArrowDown,
    ArrowLeft,
    ArrowRight,
    Home,
    End,
    Escape,
    Enter,
    Backspace
} KeyboardButton;

KeyboardButton captureKeyboardInput();

#define KEY_ESC_OR_EXTENDED 27
#define EXTEND_ARROW_RIGHT 67
#define EXTEND_ARROW_LEFT 68
#define EXTEND_ARROW_UP 65
#define EXTEND_ARROW_DOWN 66
#define EXTEND_HOME 72
#define EXTEND_END 70

#define KEY_BACKSPACE 127
#define KEY_ENTER 10
#define KEY_Y 121
KeyboardButton captureKeyboardInput()
{
    char first = getch();
    switch (first)
    {
    case KEY_ENTER:
        return Enter;
    case KEY_ESC_OR_EXTENDED:
        if (kbhit() == 0)
            return Escape;
        getch(); // skip ]
        char specialKey = getch();
        switch (specialKey)
        {
        case EXTEND_ARROW_UP:
            return ArrowUp;
        case EXTEND_ARROW_DOWN:
            return ArrowDown;
        case EXTEND_ARROW_RIGHT:
            return ArrowRight;
        case EXTEND_ARROW_LEFT:
            return ArrowLeft;
        case EXTEND_HOME:
            return Home;
        case EXTEND_END:
            return End;
        }
        // handle esc and arrow
        break;
    case KEY_BACKSPACE:
        return Backspace;
    }
}
