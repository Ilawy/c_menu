#include "./conio.h"

typedef enum
{
    ArrowUp,
    ArrowDown,
    ArrowLeft,
    ArrowRight,
    Escape,
    Enter,
    Backspace
} KeyboardButton;

KeyboardButton captureKeyboardInput();