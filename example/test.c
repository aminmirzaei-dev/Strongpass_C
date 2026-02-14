#include <stdio.h>
#include "strongpass.h"

int main(void)
{
    char password[64];

    sp_options_t options = {
        .length = 16,
        .use_lowercase = 1,
        .use_uppercase = 1,
        .use_digits = 1,
        .use_symbols = 1
    };

    if (sp_generate(password, sizeof(password), &options) != SP_OK) {
        printf("Password generation failed\n");
        return 1;
    }

    printf("Generated password: %s\n", password);

    sp_strength_t strength = sp_evaluate_strength(password);
    printf("Strength: %d\n", strength);

    return 0;
}

