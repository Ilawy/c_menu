#include <stdio.h>

// Forward declarations
typedef struct StructB StructB;
typedef struct StructA StructA;

// Define the callback function pointer types
typedef void (*CallbackA)(StructA *);
typedef void (*CallbackB)(StructB *);

// Define StructB
struct StructB
{
    int value;
    StructA *ptrToA;
    CallbackB callbackB;
};

// Define StructA
struct StructA
{
    int value;
    StructB *ptrToB;
    CallbackA callbackA;
};

// Example callback functions
void exampleCallbackA(StructA *a)
{
    printf("CallbackA called with StructA value: %d\n", a->value);
}

void exampleCallbackB(StructB *b)
{
    printf("CallbackB called with StructB value: %d\n", b->value);
}

int main()
{
    StructA a;
    StructB b;

    a.value = 10;
    b.value = 20;

    a.ptrToB = &b;
    b.ptrToA = &a;

    a.callbackA = exampleCallbackA;
    b.callbackB = exampleCallbackB;

    // Call the callbacks
    a.callbackA(&a);
    b.callbackB(&b);

    return 0;
}
