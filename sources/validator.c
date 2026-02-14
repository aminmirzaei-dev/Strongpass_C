#include "strongpass.h"
#include <string.h>
#include <ctype.h>

/*
 * Evaluate password strength based on
 * length and character variety.
 */
sp_strength_t sp_evaluate_strength(const char *password)
{
    if (!password)
        return SP_STRENGTH_WEAK;

    size_t len = strlen(password);
    int lower = 0, upper = 0, digit = 0, symbol = 0;

    for (size_t i = 0; i < len; i++) {
        if (islower(password[i])) lower = 1;
        else if (isupper(password[i])) upper = 1;
        else if (isdigit(password[i])) digit = 1;
        else symbol = 1;
    }

    int score = lower + upper + digit + symbol;

    if (len >= 12 && score >= 3)
        return SP_STRENGTH_STRONG;
    if (len >= 8 && score >= 2)
        return SP_STRENGTH_MEDIUM;

    return SP_STRENGTH_WEAK;
}

