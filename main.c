#include "stdio.h"
#include "conio.h"
#include "menu.h"
#include "inputter.h"
#include "stdm.h"
#include "keyboard.c"

//

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
        if (state->renderID)
            printf("%d)", i + 1);
        printf("%s\n", state->currentMenu->items[i]);
        resetTextColor();
        resetBackgroundColor();
    }
    int oldx = 0, oldy = 0;
    wherexy(&oldx, &oldy);
    gotoxy(0, state->winsize.ws_row);
    textbackground(WHITE);
    textcolor(RED);
    printf("ENTER / ↑ / ↓ / HOME / END");
    resetBackgroundColor();
    resetTextColor();
    gotoxy(oldx, oldy);
}

void runApp(AppState *state)
{
    Menu menu = *state->currentMenu;
    // init menu before render
    renderMenu(state);
    while (1)
    {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, state->winsize);
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
            MenuCallback callback = state->currentMenu->callbacks[state->choice];
            callback(state);
            break;
        case Home:
            state->choice = 0;
            renderMenu(state);
            break;
        case End:
            state->choice = state->currentMenu->size - 1;
            renderMenu(state);
            break;
        case Escape:
            system("clear");
            printf("Are you sure you want to exit the app (y/N)?\n");
            char ch = getch();
            if (ch == KEY_Y)
                exit(0);
            else renderMenu(state);
            break;
            ;
        }
    }
}

// menu item callback

void return_to_user_options(AppState *);

// WARINING GLOBAL VARS
// SORRY FOR USING GLOBAL VARS, WE WILL DISCUSS THIS LATER

void noop(AppState *state)
{
}

// MAIN
void main_render(AppState *state)
{
    // char str[32];
    // sprintf(state->currentMenu->items[1], "Manage Employees (%d)", state->employeesCount);
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
void return_to_new_employee(AppState *state)
{
    state->currentMenu = state->menus[MENU_NEW_EMPLOYEE];
    renderMenu(state);
}
void new_employee_render(AppState *state)
{
    if (state->employeesCount >= MAX_EMPLOYEE_LEN)
    {
        printf("Too many employees, press any key to go back\n");
        getch();
        return_to_main(state);
        return;
    }

    char name[32];
    int salary = 0;
    int day = 0;
    int month = 0;
    int year = 0;
    printf("Enter name: ");
    // https://stackoverflow.com/a/56095515
    // %[*][width][modifiers]type
    scanf("%[^\n]%c", name);
    fgetc(stdin);
    while (strlen(name) == 0 || strlen(name) > 32)
    {
        printf("Please enter a name: ");
        scanf("%[^\n]%c", name);
        fgetc(stdin);
    }
    salary = prompt_int("Enter salary(numbers only): ");
    printf("\n");
    while (salary <= 0)
    {
        printf("salary must be greater than 0\n");
        salary = prompt_int("Enter salary(numbers only): ");
        printf("\n");
    }
    day = prompt_int("Enter birth day(numbers only): ");
    printf("\n");
    while (day <= 0 || day > 31)
    {
        printf("day must be between 1 and 31\n");
        day = prompt_int("Enter birth day(numbers only): ");
        printf("\n");
    }
    month = prompt_int("Enter birth month(numbers only): ");
    printf("\n");
    while (month <= 0 || month > 12)
    {
        printf("month must be between 1 and 12\n");
        month = prompt_int("Enter birth month(numbers only): ");
        printf("\n");
    }
    year = prompt_int("Enter birth year(numbers only): ");
    while (year <= MIN_EMPLOYEE_BYEAR)
    { // SUBJECT TO CHANGE
        printf("year must be greater than 0\n");
        year = prompt_int("Enter birth year(numbers only): ");
        printf("\n");
    }
    printf("\n");
    Date bDate = {
        .day = day,
        .month = month,
        .year = year};
    Employee emp = {.salary = salary, .id = state->uniq, .bDate = bDate};
    strcpy(emp.name, name);
    state->employees[state->employeesCount] = emp;
    state->employeesCount++;
    state->uniq++;
    return_to_main(state);
}
/*


*/

// MANAGE EMPLOYEES
void return_to_manage_employees(AppState *state)
{
    state->choice = 0;
    state->currentMenu = state->menus[MENU_MANAGE_EMPLOYEES];
    renderMenu(state);
}
void manage_employees_render(AppState *state)
{
    for (int i = 0; i < state->employeesCount; i++)
    {
        char title[32];
        sprintf(title, "[%d] %s", state->employees[i].id, state->employees[i].name);
        strcpy(state->currentMenu->items[i], title);
        // *state->currentMenu->items[i] = staff[i].name;
        state->currentMenu->callbacks[i] = &return_to_user_options;
    }

    state->currentMenu->size = state->employeesCount + 1; // +1 for back
    strcpy(state->currentMenu->items[state->employeesCount], "Back");
    state->currentMenu->callbacks[state->employeesCount] = &return_to_main;
}
/*


*/

// EMPLOYEE OPTIONS
void return_to_user_options(AppState *state)
{
    state->currentMenu = state->menus[MENU_USER_OPTIONS];
    // this one was good, i like it
    state->generic[GENERIC_CURRENT_USER_INDEX] = state->choice;
    state->choice = 0;
    renderMenu(state);
}
void user_options_render(AppState *state)
{
}

void employee_show(AppState *state)
{
    Employee currentEmployee = state->employees[state->generic[GENERIC_CURRENT_USER_INDEX]];
    system("clear");
    printEmployee(currentEmployee);
    printf("Press any key to go back");
    getch();
    return_to_user_options(state);
}

// EMPLOYEE MODIFY
void return_to_employee_modify(AppState *state)
{
    state->currentMenu = state->menus[MENU_EMPLOYEE_MODIFY];
    state->choice = 0;
    printf("%s", state->currentMenu->title);
    renderMenu(state);
}

void employee_modify_name(AppState *state)
{
    Employee currentEmployee = state->employees[state->generic[GENERIC_CURRENT_USER_INDEX]];
    system("clear");
    printf("Enter new name: ");
    char name[32] = {0};
    // scanf("%[^\n]%c", name);
    scanf("%32[^\n]%c", name);
    fgetc(stdin);
    strcpy(state->employees[state->generic[GENERIC_CURRENT_USER_INDEX]].name, name);
    return_to_employee_modify(state);
}
void employee_modify_salary(AppState *state)
{
    Employee currentEmployee = state->employees[state->generic[GENERIC_CURRENT_USER_INDEX]];
    system("clear");
    int salary = prompt_int("Enter new salary: ");
    state->employees[state->generic[GENERIC_CURRENT_USER_INDEX]].salary = salary;
    return_to_employee_modify(state);
}
void employee_modify_bdate(AppState *state)
{
    Employee currentEmployee = state->employees[state->generic[GENERIC_CURRENT_USER_INDEX]];
    system("clear");
    // day
    int day = prompt_int("Enter day: ");
    printf("\n");
    while (day <= 0 || day > 31)
    {
        day = prompt_int("Enter a valid day (between 1 and 31): ");
        printf("\n");
    }
    // month
    int month = prompt_int("Enter month: ");
    printf("\n");
    while (month < 1 || month > 12)
    {
        month = prompt_int("Enter a valid month (between 1 and 12): ");
        printf("\n");
    }
    // year
    int year = prompt_int("Enter year: ");
    printf("\n");
    while (year <= MIN_EMPLOYEE_BYEAR)
    {
        year = prompt_int("Enter a valid year (more than 1924): ");
        printf("\n");
    }

    // assign
    state->employees[state->generic[GENERIC_CURRENT_USER_INDEX]].bDate.day = day;
    state->employees[state->generic[GENERIC_CURRENT_USER_INDEX]].bDate.month = month;
    state->employees[state->generic[GENERIC_CURRENT_USER_INDEX]].bDate.year = year;
    return_to_employee_modify(state);
}

void employee_delete(AppState *state)
{
    Employee currentEmployee = state->employees[state->generic[GENERIC_CURRENT_USER_INDEX]];
    int deleted_index = -1;
    for (int i = 0; i < MAX_EMPLOYEE_LEN; i++)
    {
        Employee *emp = &state->employees[i];
        if (emp->id == currentEmployee.id)
        {
            deleted_index = i;
            state->employees[i] = (Employee){};
        }
        else if (deleted_index != -1)
        {
            state->employees[i - 1] = *emp;
        }
        // for(int i = 0;)
    }
    state->employeesCount--;
    if (state->employeesCount > 0)
        return_to_manage_employees(state);
    else
        return_to_main(state);
    // exit(3);
}

void employee_modify_render(AppState *state)
{
    Employee currentEmployee = state->employees[state->generic[GENERIC_CURRENT_USER_INDEX]];
    state->currentMenu->size = 4; // name - salary - birthdate - back

    // name
    sprintf(state->currentMenu->items[0], "Change name (%s)", currentEmployee.name);
    state->currentMenu->callbacks[0] = &employee_modify_name;

    // salary
    sprintf(state->currentMenu->items[1], "Change salary (%d)", currentEmployee.salary);
    state->currentMenu->callbacks[1] = &employee_modify_salary;

    // bdate
    sprintf(state->currentMenu->items[2], "Change birth date (%d/%d/%d)", currentEmployee.bDate.day, currentEmployee.bDate.month, currentEmployee.bDate.year);
    state->currentMenu->callbacks[2] = &employee_modify_bdate;

    // back
    sprintf(state->currentMenu->items[3], "back");
    state->currentMenu->callbacks[3] = &return_to_user_options;
}

// EMPLOYEE METHODS

int main()
{

    Menu mainMenu = {
        .title = "Main Menu",
        .size = 3,
        .items = {"New Employee", "Manage Employees", "Quit"},
        .callbacks = {&return_to_new_employee, &return_to_manage_employees, &noop},
        .onRender = &main_render};

    Menu newEmployeeMenu = {
        .title = "New Employee",
        .size = 0,
        .items = {},
        .onRender = &new_employee_render,
        .callbacks = {&return_to_main}};

    Menu manageEmployeesMenu = {
        .title = "Manage Employees",
        .size = 0,
        .items = {},
        .onRender = &manage_employees_render,
        .callbacks = {&return_to_main}};

    Menu userOptionsMenu = {
        .title = "User Options",
        .size = 4,
        .items = {"Show", "Modify", "Delete", "Return"},
        .onRender = &user_options_render,
        .callbacks = {&employee_show, &return_to_employee_modify, &employee_delete, &return_to_manage_employees}};

    Menu employeeModifyMenu = {
        .title = "User Modification",
        .size = 0,
        .items = {},
        .onRender = &employee_modify_render

    };
    struct winsize w;

    AppState state = {
        .choice = 0,
        .running = 1,
        .employees = {0},
        .employeesCount = 0,
        .uniq = 1,
        .renderID = 0,
        .winsize = w,
        .currentMenu = &mainMenu};
    state.menus[MENU_MAIN] = &mainMenu;
    state.menus[MENU_NEW_EMPLOYEE] = &newEmployeeMenu;
    state.menus[MENU_MANAGE_EMPLOYEES] = &manageEmployeesMenu;
    state.menus[MENU_USER_OPTIONS] = &userOptionsMenu;
    state.menus[MENU_EMPLOYEE_MODIFY] = &employeeModifyMenu;

    runApp(&state);
    return 0;
}
