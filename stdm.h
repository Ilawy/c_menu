typedef enum MErrorCode{
    ErrSmallSize = -1,
    ErrNoError = 0
} MErrorCode;


int string_len(char []);
MErrorCode string_cat(char [], char[], int);
int string_cmp(char[], char[]);
MErrorCode string_cpy(char[], char[], int);

void string_upper(char target[]);
void string_lower(char target[]);