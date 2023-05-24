#include <stdlib.h>

int _setenv(const char *name, const char *value, int overwrite) {
    if (name == NULL || value == NULL)
        return -1;

    return setenv(name, value, overwrite);
}
