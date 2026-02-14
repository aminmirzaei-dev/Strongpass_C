#include <unistd.h>
#include <fcntl.h>

/*
 * Read cryptographically secure random bytes
 * from /dev/urandom.
 */
int sp_get_entropy(void *buffer, size_t size) {
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0)
        return -1;

    ssize_t result = read(fd, buffer, size);
    close(fd);

    return (result == (ssize_t)size) ? 0 : -1;
}

