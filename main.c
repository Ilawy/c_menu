#include "stdio.h"
#include "conio.h"
#include "stdm.c"
#include "menu.h"
#include "inputter.h"

#define MAX_STAFF_COUNT 10

#define MENU_MAIN 0
#define MENU_NEW_EMPLOYEE 1
#define MENU_MANAGE_EMPLOYEES 2
#define MENU_USER_OPTIONS 3

void renderMenu(AppState *state)
{
    system("clear");
    printf("%s\n", state->currentMenu->title);
    //
    state->currentMenu->onRender(state);
    for (int i = 0; i < state->currentMenu->size; i++)
    {
        if (state->choice == i)
        {
            textbackground(WHITE);
            textcolor(BLUE);
        }

        printf("%d) %s\n", i, state->currentMenu->items[i]);
        resetTextColor();
        resetBackgroundColor();
    }
}

void runApp(AppState *state)
{
    Menu menu = *state->currentMenu;
    // init menu before render
    renderMenu(state);
    while (1)
    {
        KeyboardButton button = captureKeyboardInput();
        switch (button)
        {
        // https://vanslaars.io/articles/cycle-through-an-array-of-values-with-the-modulus-operator/
        case ArrowDown:
            state->choice = (state->choice + 1) % state->currentMenu->size;
            renderMenu(state);
            break;
        case ArrowUp:
            state->choice = (state->choice - 1 + state->currentMenu->size) % state->currentMenu->size;
            renderMenu(state);
            break;
        case Enter:
            // printf("FUCK OFF %p", state->currentMenu->callbacks[state->choice]);
            MenuCallback callback = state->currentMenu->callbacks[state->choice];
            printf("FUCK OFF %p\n", callback);
            callback(state);
            break;
        }
    }
}

// menu item callback

typedef struct Date
{
    char day;
    char month;
    int year;

} Date;

typedef struct Employee
{
    int id;
    char name[32];
    int salary;
    Date bDate;

} Employee;

void user_options_callback(AppState *);

// WARINING GLOBAL VARS
// SORRY FOR USING GLOBAL VARS, WE WILL DISCUSS THIS LATER
Employee staff[MAX_STAFF_COUNT];
int employeeCount = 0;

void noop(AppState *state)
{
}

// MAIN
void main_init(AppState *state)
{
    char str[32];
    sprintf(state->currentMenu->items[1], "Manage Employees (%d)", employeeCount);
    // set second item of the menu
    printf("MY SIZE: %d\n", state->currentMenu->size);
}
void return_to_main(AppState *state)
{
    state->choice = 0;
    state->currentMenu = state->menus[MENU_MAIN];
    renderMenu(state);
}
/*


*/

// NEW EMPLOYEE
void new_employee_callback(AppState *state)
{
    state->currentMenu = state->menus[MENU_NEW_EMPLOYEE];
    renderMenu(state);
}
void new_employee_init(AppState *state)
{
    if (employeeCount >= MAX_STAFF_COUNT)
    {
        printf("Too many employees, press any key to go back\n");
        getch();
        state->currentMenu = state->menus[MENU_MAIN];
        system("clear");
        renderMenu(state);
        return;
    }

    char name[32];
    int salary = 0;
    int day = 0;
    int month = 0;
    int year = 0;
    printf("Enter name: ");
    fgets(name, 32, stdin);
    printf("HELLO %s", name);
    // salary = prompt_int("Enter salary(numbers only): ");
    // printf("\n");
    // while (salary <= 0)
    // {
    //     printf("salary must be greater than 0\n");
    //     salary = prompt_int("Enter salary(numbers only): ");
    //     printf("\n");
    // }
    // day = prompt_int("Enter birth day(numbers only): ");
    // printf("\n");
    // while (day <= 0 || day > 31)
    // {
    //     printf("day must be between 1 and 31\n");
    //     day = prompt_int("Enter birth day(numbers only): ");
    //     printf("\n");
    // }
    // month = prompt_int("Enter birth month(numbers only): ");
    // printf("\n");
    // while (month <= 0 || month > 12)
    // {
    //     printf("month must be between 1 and 12\n");
    //     month = prompt_int("Enter birth month(numbers only): ");
    //     printf("\n");
    // }
    // year = prompt_int("Enter birth year(numbers only): ");
    // while (year <= 1950)
    // { // SUBJECT TO CHANGE
    //     printf("year must be greater than 0\n");
    //     year = prompt_int("Enter birth year(numbers only): ");
    //     printf("\n");
    // }
    // printf("\n");
    Date bDate = {
        .day = day,
        .month = month,
        .year = year};
    Employee emp = {.name = name, .salary = salary, .id = employeeCount, .bDate = bDate};
    staff[employeeCount] = emp;
    strcpy(emp.name, name);
    employeeCount++;
    // printf("SHIT");
    // renderMenu(state);
    // exit(3);
    return_to_main(state);
}
/*


*/

// MANAGE EMPLOYEES
void manage_employees_callback(AppState *state)
{
    state->choice = 0;
    state->currentMenu = state->menus[MENU_MANAGE_EMPLOYEES];
    renderMenu(state);
}
void manage_employees_init(AppState *state)
{
    for (int i = 0; i < employeeCount; i++)
    {
        char title[32];
        // printf("-%s-\n\n", &staff[i].name[0]);
        // sprintf(title, "[%d] %s", staff[i].id, staff[i].name);
        strcpy(state->currentMenu->items[i], staff[i].name);
        // *state->currentMenu->items[i] = staff[i].name;
        state->currentMenu->callbacks[i] = &user_options_callback;
    }

    state->currentMenu->size = employeeCount + 1; // +1 for back
    strcpy(state->currentMenu->items[employeeCount], "Back");
    state->currentMenu->callbacks[employeeCount] = &return_to_main;

    // state->choice = 0;
}
/*


*/

// EMPLOYEE OPTIONS
void user_options_callback(AppState *state)
{
    state->currentMenu = state->menus[MENU_USER_OPTIONS];
    renderMenu(state);
}
void user_options_init(AppState *state)
{
    // printf("YO");
}

// why did you do this?
//  to be able to set the main menu again from other menus

int main()
{

    Menu mainMenu = {
        .title = "Main Menu",
        .size = 3,
        .items = {"New Employee", "Manage Employees", "Quit"},
        .callbacks = {&new_employee_callback, &manage_employees_callback, &noop},
        .onRender = &main_init};

    Menu newEmployeeMenu = {
        .title = "New Employee",
        .size = 0,
        .items = {"Fuck OFF"},
        .onRender = &new_employee_init,
        .callbacks = {&return_to_main}};

    Menu manageEmployeesMenu = {
        .title = "Manage Employees",
        .size = 0,
        .items = {},
        .onRender = &manage_employees_init,
        .callbacks = {&return_to_main}};

    Menu userOptionsMenu = {
        .title = "User Options",
        .size = 4,
        .items = {"Show", "Modify", "Delete", "Return"},
        .onRender = &user_options_init,
        .callbacks = {&noop, &noop, &noop, &manage_employees_callback}};

    AppState state = {
        .choice = 0,
        .running = 1,
        .currentMenu = &newEmployeeMenu};
    state.menus[MENU_MAIN] = &mainMenu;
    state.menus[MENU_NEW_EMPLOYEE] = &newEmployeeMenu;
    state.menus[MENU_MANAGE_EMPLOYEES] = &manageEmployeesMenu;
    state.menus[MENU_USER_OPTIONS] = &userOptionsMenu;
    runApp(&state);
    return 0;
}
