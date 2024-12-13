#include "return_code.h"

char RETURN_CODE = 0x00;

void return_code_set(char code)
{
    RETURN_CODE = code;
}