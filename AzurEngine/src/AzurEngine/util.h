#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <stdio.h>

#define ERROR_EXIT(...) fprintf(stderr, __VA_ARGS__)
#define ERROR_RETURN(R, ...) fprintf(stderr, __VA_ARGS__); return R

#endif // _GLOBAL_H