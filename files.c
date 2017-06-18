#include <sys/stat.h>
#include <sys/types.h>

#ifdef __MINGW32__
#include <direct.h>
#endif

#include "files.h"

int make_directory(char *name, mode_t mode)
{
#ifdef __linux__
    return mkdir(name, mode);
#else
    return _mkdir(name);
#endif
}

