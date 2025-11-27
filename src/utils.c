#include "utils.h"

int encode_url(char *dest, size_t dest_size, const char *src)
{
    size_t di = 0;

    for (size_t si = 0; src[si] != '\0'; si++)
    {
        unsigned char c = (unsigned char)src[si];

        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
        {
            if (di + 1 >= dest_size)
                return -1;
            dest[di++] = c;
        }
        else
        {
            if (di + 3 >= dest_size)
                return -1;
            snprintf(&dest[di], 4, "%%%02X", c);
            di += 3;
        }
    }

    if (di >= dest_size)
        return -1;
    dest[di] = '\0';
    return 0;
}