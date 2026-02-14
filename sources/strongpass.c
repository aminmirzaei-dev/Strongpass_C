#include "strongpass.h"
#include <string.h>

/* Internal entropy function */
int sp_get_entropy(void *buffer, size_t size);

/* Character sets */
static const char LOWER[]   = "abcdefghijklmnopqrstuvwxyz";
static const char UPPER[]   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char DIGITS[]  = "0123456789";
static const char SYMBOLS[] = "!@#$%^&*";

/*
 * Generate a secure password based on options.
 */
sp_error_t sp_generate(char *buffer, size_t buffer_size,
                       const sp_options_t *opt)
{
    if (!buffer || !opt || opt->length == 0)
        return SP_ERR_INVALID_OPTION;

    if (buffer_size < opt->length + 1)
        return SP_ERR_BUFFER_TOO_SMALL;

    char charset[128] = {0};
    size_t charset_len = 0;

    if (opt->use_lowercase)
        strcat(charset, LOWER);
    if (opt->use_uppercase)
        strcat(charset, UPPER);
    if (opt->use_digits)
        strcat(charset, DIGITS);
    if (opt->use_symbols)
        strcat(charset, SYMBOLS);

    charset_len = strlen(charset);
    if (charset_len == 0)
        return SP_ERR_INVALID_OPTION;

    unsigned char rnd[opt->length];
    if (sp_get_entropy(rnd, opt->length) != 0)
        return SP_ERR_NO_ENTROPY;

    for (size_t i = 0; i < opt->length; i++) {
        buffer[i] = charset[rnd[i] % charset_len];
    }

    buffer[opt->length] = '\0';
    return SP_OK;
}

