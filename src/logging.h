#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <signal.h>
#include <unistd.h>
#include <stdint.h>
#include <stdarg.h>


#ifndef HELPER_H
#define HELPER_H

#define imin(x, y) (x > y ? y : x)
#define imax(x, y) (x > y ? x : y)

typedef struct debug_lvl {
    uint32_t id;
    char *name;
    char *color_code;
} debug_lvl;

extern const debug_lvl DEBUG_VERBOSE;
extern const debug_lvl DEBUG_INFO;
extern const debug_lvl DEBUG_WARNING;
extern const debug_lvl DEBUG_ERROR;

#define DEBUG_LVL DEBUG_INFO

int logm(const debug_lvl level, const char *str, ...);


typedef struct time_data {
    char *host;
    uint16_t n;
    uint32_t rt_disp;
    uint32_t req_disp_sec;
    uint32_t req_disp_fract;
    uint32_t delay_sec;
    uint32_t delay_fract;
    uint32_t offset_sec;
    uint32_t offset_fract;
} time_data;


void print_out_format_td(time_data td);


void print_out_format_r(
    const char *host,
    const uint16_t n,
    const uint32_t rt_disp,
    const int32_t req_disp_sec,
    const uint32_t req_disp_fract,
    const uint32_t delay_sec,
    const uint32_t delay_fract,
    const int32_t offset_sec,
    const uint32_t offset_fract);


char *print_as_hexdump(void *data, uint64_t len);

char *print_arr(uint8_t *nums, uint64_t len);

char *print_binary(uint8_t byte);


void *resize_arr(void *arr, uint64_t memb, uint64_t old_length, uint64_t new_length);


// ---------------------------CALCULATION HELPERS---------------------------
/*
uint32_t fraction_to_ns(uint32_t fraction);

uint32_t ns_to_fraction(uint32_t ns);


uint32_t arr_to_uint32(uint8_t *arr, uint64_t max_len);

uint64_t arr_to_uint64(uint8_t *arr, uint64_t max_len);


void uint32_to_arr(uint32_t i, uint8_t **ret_arr, uint32_t max_len);

void uint64_to_arr(uint64_t i, uint8_t **ret_arr, uint32_t max_len);
*/
#endif
