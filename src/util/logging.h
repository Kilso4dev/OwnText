#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef CRISP_OUTPUT_H
#define CRISP_OUTPUT_H



typedef struct debug_lvl
{
	uint32_t id;
	char *name;
	char *color_code;
} debug_lvl;

extern const debug_lvl DEBUG_VERBOSE;
extern const debug_lvl DEBUG_INFO;
extern const debug_lvl DEBUG_WARNING;
extern const debug_lvl DEBUG_ERROR;

int logm(const debug_lvl level, const char *str, ...);

#endif //CRISP_OUTPUT_H
