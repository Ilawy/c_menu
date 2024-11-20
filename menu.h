#include "stdio.h"

#define MAX_MENU_ITEMS 16
#define MAX_STATE_MENUS 15
#define MAX_MENU_TITLE_LEN 16
#define MAX_ITEM_LEN 32
#define GENERIC_LEN 4

typedef struct Menu Menu;
typedef struct AppState AppState;
typedef void (*MenuCallback)(AppState *);

typedef struct Menu
{
    char title[MAX_MENU_TITLE_LEN];
    int size;
    char items[MAX_MENU_ITEMS][MAX_ITEM_LEN];
    MenuCallback callbacks[MAX_MENU_ITEMS];
    MenuCallback onRender;

} Menu;
typedef struct AppState
{
    Menu *currentMenu;
    Menu *menus[MAX_STATE_MENUS];
    int choice;
    char running;

    int generic[GENERIC_LEN];
} AppState;
