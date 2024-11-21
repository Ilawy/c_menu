#include "stdio.h"
#include "stdm.c"


int main(){
    //strlen
    printf("String length: %d\n", string_len("mina"));
    printf("String length 2: %d\n", string_len("mohammed"));

    //strcat
    char name_cat_1[64] = "Mohammed";
    char name_cat_2[8] = " Amr";
    string_cat(name_cat_1, name_cat_2, 64);
    printf("Cat result: %s\n", name_cat_1);

    printf("Compare result: %d\n", string_cmp("A", "a"));


    char name_cpy_1[64];
    char name_cpy_2[16] = "Mohammed";
    string_cpy(name_cpy_1, name_cpy_2, 64);
    printf("String copy result: %s -- %s\n", name_cpy_1, name_cpy_2);

    char name_upper[] = "HELLO hello HELLO";
    string_upper(name_upper);
    printf("%s\n", name_upper);

    char name_lower[] = "HELLO hello HELLO";
    string_lower(name_lower);
    printf("%s\n", name_lower);

    return 0;
}