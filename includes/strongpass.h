#ifndef STRONGPASS_H
#define STRONGPASS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

 // Error codes
typedef enum {
    SP_OK = 0,
    SP_ERR_INVALID_OPTION,
    SP_ERR_NO_ENTROPY,
    SP_ERR_BUFFER_TOO_SMALL
} sp_error_t;

 //Password strength levels
typedef enum {
    SP_STRENGTH_WEAK,
    SP_STRENGTH_MEDIUM,
    SP_STRENGTH_STRONG
} sp_strength_t;

// Options for password generation
typedef struct {
    size_t length;        /* Desired password length */
    int use_lowercase;    /* a-z */
    int use_uppercase;    /* A-Z */
    int use_digits;       /* 0-9 */
    int use_symbols;      /* !@#$%^&* */
} sp_options_t;

/* =========================
 * Generate a secure password
 *
 * buffer      : output buffer
 * buffer_size : size of output buffer
 * options     : generation options
 * ========================= */
sp_error_t sp_generate(
    char *buffer,
    size_t buffer_size,
    const sp_options_t *options
);

 // Evaluate password strength
sp_strength_t sp_evaluate_strength(const char *password);

#ifdef __cplusplus
}
#endif

#endif /* STRONGPASS_H */


