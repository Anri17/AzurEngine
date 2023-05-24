#ifndef _AZUR_MEMORY_LEAK_FINDER_H
#define _AZUR_MEMORY_LEAK_FINDER_H

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__)
#define new DBG_NEW
#else
#define DBG_NEW new
#endif

#endif // _AZUR_MEMORY_LEAK_FINDER_H