#include "logging.h"

uint32_t fraction_to_ns(uint32_t fraction);
uint32_t ns_to_fraction(uint32_t nsecs);



const debug_lvl DEBUG_VERBOSE = {.id = 0x1 << 1, .name = "VERBOSE", .color_code = "\033[0;37m"};
const debug_lvl DEBUG_INFO = {.id = 0x1 << 2, .name = "INFO", .color_code = "\033[0;36m"};
const debug_lvl DEBUG_WARNING = {.id = 0x1 << 3, .name = "WARNING", .color_code = "\033[0;33m"};
const debug_lvl DEBUG_ERROR = {.id = 0x1 << 4, .name = "ERROR", .color_code = "\033[0;31m"};


int logm(const debug_lvl level, const char *str, ...) {
    struct timespec time_unix;
    clock_gettime(CLOCK_REALTIME, &time_unix);
    if (level.id >= DEBUG_LVL.id) {
        struct tm *tm = localtime(&time_unix.tv_sec);

        va_list args;
        va_start(args, str);

        fprintf(stderr, "[%4d-%02d-%02d  %2d:%02d:%02d: %6lu] [%s%-10s\033[0m]\t",
        tm->tm_year + 1900,
        tm->tm_mon + 1,
        tm->tm_mday,
        tm->tm_hour,
        tm->tm_min,
        tm->tm_sec,
        (time_unix.tv_nsec/1000), level.color_code, level.name);

        int ret = vfprintf(stderr, str, args);
        fprintf(stderr, "\n");
        va_end(args);
        return ret;
    }
    return 0;
}

void print_out_format_td(time_data td) {
    print_out_format_r(td.host, td.n, td.rt_disp, td.req_disp_sec, td.req_disp_fract, td.delay_sec, td.delay_fract, td.offset_sec, td.offset_fract);
}

void print_out_format_r(
    const char *host,
    const uint16_t n,
    const uint32_t rt_disp,
    const int32_t req_disp_sec,
    const uint32_t req_disp_fract,
    const uint32_t delay_sec,
    const uint32_t delay_fract,
    const int32_t offset_sec,
    const uint32_t offset_fract) {

    printf("%s;%u;%u.%06u;%d.%06u;%u.%06u;%d.%06u\n",
    host,
    n,
    rt_disp >> 16,
    fraction_to_ns((rt_disp << 16)) / (uint32_t)1000, // fraction to nanosecs to microsecs
    req_disp_sec,
    fraction_to_ns(req_disp_fract) / (uint32_t)1000, // fraction to nanosecs to microsecs
    delay_sec,
    fraction_to_ns(delay_fract) / (uint32_t)1000, // fraction to nanosecs to microsecs
    offset_sec,
    fraction_to_ns(offset_fract) / (uint32_t)1000); // fraction to nanosecs to microsecs

    logm(DEBUG_INFO, "%s;%u;%u.%06u;%u.%06u;%u.%06u;%d.%06u\n",
    host,
    n,
    rt_disp >> 16,
    fraction_to_ns((rt_disp << 16)) / (uint32_t)1000, // fraction to nanosecs to microsecs
    req_disp_sec,
    fraction_to_ns(req_disp_fract) / (uint32_t)1000, // fraction to nanosecs to microsecs
    delay_sec,
    fraction_to_ns(delay_fract) / (uint32_t)1000, // fraction to nanosecs to microsecs
    offset_sec,
    fraction_to_ns(offset_fract) / (uint32_t)1000); // fraction to nanosecs to microsecs
}

//TODO refactor print_as_hexdump() to give back a string instead of printing directly
char *print_as_hexdump(void *data, uint64_t len) {
    uint8_t *buf = (uint8_t *)data;
    //print data as hexdump
    const int bytes_per_line = 16;
    const int bytes_per_block = 2;
    for (uint64_t i = 0; i < len;) {
        fprintf(stderr, "%08lx ", i);
        for (uint64_t j = 0; j < bytes_per_line; j+=bytes_per_block) {
            for (int k = 0; k < bytes_per_block; k++) {
                fprintf(stderr, "%02x", i<len?buf[i]:0);
                i++;
            }
            fprintf(stderr, " ");
        }
        fprintf(stderr, " ");
        i -= bytes_per_line;
        for (int k = 0; k < bytes_per_line; k++) {
            fprintf(stderr, "%c", i<len?((buf[i]>=32 && buf[i]<127)?buf[i]:'.'):'.');
            i++;
        }
        fprintf(stderr, "\n");
    }
    return NULL;
}

//TODO refactor print_arr() to give back a string instead of printing directly
char *print_arr(uint8_t *nums, uint64_t len) {
    fprintf(stderr, "(");
    for (int i = 0; i < len; i++) {
        fprintf(stderr, "%d", nums[i]);
        if (i != (len-1)) {
            fprintf(stderr, ", ");
        }
    }
    fprintf(stderr, ")");
    return NULL;
}

//TODO refactor print_binary() to give back a string instead of printing directly
char *print_binary(uint8_t byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", 0x1 & ((byte) >> i));
    }
    return NULL;
}


void *resize_arr(void *arr, uint64_t memb, uint64_t old_length, uint64_t new_length) {
    void *new_arr = malloc(new_length *memb);
    if (arr != NULL) {
        if (new_arr != NULL) {
            new_arr = memcpy(new_arr, arr, imin(new_length, old_length) * memb);
            free(arr);
            arr = new_arr;

            return arr;
        } else return NULL;
    } else {
        if (new_arr != NULL) {
            return new_arr;
        } else return NULL;
    }
}


// ---------------------------CALCULATION HELPERS---------------------------
#define SIZE_FACTOR 1000000000 // nano seconds multiplier

uint32_t fraction_to_ns(uint32_t fraction) {
    return (uint32_t)((((uint64_t)fraction) * SIZE_FACTOR) >> 32);
}

uint32_t ns_to_fraction(uint32_t nsecs) {
    return (uint32_t) (((((uint64_t)nsecs) << 32) / SIZE_FACTOR));
}


uint32_t arr_to_uint32(uint8_t *arr, uint64_t max_len) {
    const int byte_len = 4;
    uint32_t res = 0;
    for (uint64_t i = 0; i < byte_len; i++) {
        if (i < max_len) {
            res |= arr[i];
        }
        if (i != byte_len-1) {
            res <<= 8;
        }
    }
    return res;
}

uint64_t arr_to_uint64(uint8_t *arr, uint64_t max_len) {
    const int byte_len = 8;
    uint64_t res = 0;
    for (uint64_t i = 0; i < byte_len; i++) {
        if (i < max_len) {
            res |= arr[i];
        }
        if (i != byte_len-1) {
            res <<= 8;
        }
    }
    return res;
}


void uint32_to_arr(uint32_t i, uint8_t **ret_arr, uint32_t max_len) {
    const unsigned int byte_len = 4;
    int32_t min = imin(max_len-1, byte_len-1);

    for (int64_t j = 0; j <= min; j++) {
        (*ret_arr)[j] = ((i >> (8 * (min-j))) & 0xFF);
    }
}

void uint64_to_arr(uint64_t i, uint8_t **ret_arr, uint32_t max_len) {
    const unsigned int byte_len = 8;
    int64_t min = imin(max_len-1, byte_len-1);

    for (int64_t j = min; j >= 0; j--) {
        (*ret_arr)[j] = ((i >> (8 * (min-j))) & 0xFF);
    }
}
