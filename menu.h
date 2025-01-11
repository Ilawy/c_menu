#include "stdio.h"
#include <sys/ioctl.h>


#define MAX_MENU_ITEMS 16
#define MAX_STATE_MENUS 15
#define MAX_MENU_TITLE_LEN 64
#define MAX_ITEM_LEN 32
#define GENERIC_LEN 4

#define MAX_EMPLOYEE_LEN 10
#define MIN_EMPLOYEE_BYEAR 1924

#define MENU_MAIN 0
#define MENU_NEW_EMPLOYEE 1
#define MENU_MANAGE_EMPLOYEES 2
#define MENU_USER_OPTIONS 3
#define MENU_EMPLOYEE_MODIFY 4

#define GENERIC_CURRENT_USER_INDEX 0


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

    Employee employees[MAX_EMPLOYEE_LEN];
    int employeesCount;
    int uniq;

    char renderID;

    struct winsize winsize;

    int generic[GENERIC_LEN];
} AppState;


void printEmployee(Employee emp){
    printf("----------\n\
Name: %s\n\
ID: %d\n\
SALARY: %d\n\
B.Date: %d/%d/%d\n\
----------\n", emp.name, emp.id, emp.salary, emp.bDate.day, emp.bDate.month, emp.bDate.year);
}
