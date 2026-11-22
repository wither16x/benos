#include "lib/chars.h"
#include "lib/types.h"

bool_t isalpha(char ch)
{
    return islower(ch) || isupper(ch);
}

bool_t islower(char ch)
{
    return ch >= 'a' && ch <= 'z';
}

bool_t isupper(char ch)
{
    return ch >= 'A' && ch <= 'Z';
}

char to_upper(char ch)
{
    return ch + 'A' - 'a';
}
