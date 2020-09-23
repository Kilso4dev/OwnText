#include "logging.h"

// Enable Debugging Log

#define LOG_DEBUG 

// Starting logging with fixed size strings of length:

#define LOG_MAX_STRING_VAL 128

// Logging file

#define LOG_FILENAME "newest.log"

// Current debug level

#define DEBUG_LVL DEBUG_VERBOSE

// uncomment for output over the console and/or to a file

#define LOG_OUTPUT_FILE
#define LOG_OUTPUT_CONSOLE




const debug_lvl DEBUG_VERBOSE = {.id = 0x1 << 1, .name = "VERBOSE", .color_code = "\033[0;37m"};       
const debug_lvl DEBUG_INFO = {.id = 0x1 << 2, .name = "INFO", .color_code = "\033[0;36m"};             
const debug_lvl DEBUG_WARNING = {.id = 0x1 << 3, .name = "WARNING", .color_code = "\033[0;33m"};
const debug_lvl DEBUG_ERROR = {.id = 0x1 << 4, .name = "ERROR", .color_code = "\033[0;31m"};


#ifdef LOG_DEBUG

int logm(const debug_lvl level, const char *str, ...) {
    struct timespec time_unix;                                                                         
    clock_gettime(CLOCK_REALTIME, &time_unix);                                                         
    if (level.id >= DEBUG_LVL.id) {
        struct tm *tm = localtime(&time_unix.tv_sec);        
         
        int writtenChars = 0;
        unsigned int current_max = LOG_MAX_STRING_VAL;      

        writtenChars = 0;
        current_max = LOG_MAX_STRING_VAL;

        char *date_string_cons = NULL;
        char *date_string_file = NULL;
        
        do {
            if (writtenChars > current_max) {
                current_max = writtenChars;

                if (date_string_cons) {
                    free(date_string_cons);
                    date_string_cons = NULL;
                }
                if (date_string_file) {
                    free(date_string_file);
                    date_string_file = NULL;
                }
            }

            date_string_cons = malloc(sizeof(char) * current_max);
            date_string_file = malloc(sizeof(char) * current_max);

            
            writtenChars = snprintf(date_string_cons, current_max, "[%4d-%02d-%02d  %2d:%02d:%02d] [%s%-10s\033[0m]\t",
                    tm->tm_year + 1900,
                    tm->tm_mon + 1,
                    tm->tm_mday,
                    tm->tm_hour,
                    tm->tm_min,
                    tm->tm_sec,
                    level.color_code, level.name);
            
            snprintf(date_string_file, current_max, "[%4d-%02d-%02d  %2d:%02d:%02d] [%-10s]\t",
                    tm->tm_year + 1900,
                    tm->tm_mon + 1,
                    tm->tm_mday,
                    tm->tm_hour,
                    tm->tm_min,
                    tm->tm_sec,
                    level.name);

            
            current_max = writtenChars;

        } while (writtenChars > current_max);


        // actual arg printing
        va_list args;                                                                                  
        va_start(args, str);
        

        current_max = LOG_MAX_STRING_VAL;
        
        char *arg_string = NULL;
        do {
            if (writtenChars > current_max) {
                current_max = writtenChars;
                
                if (arg_string) {
                    free(arg_string);
                    arg_string = NULL;
                }
            }

            arg_string = malloc(sizeof(char) * current_max);

            writtenChars = vsnprintf(arg_string, current_max, str, args);

        } while (writtenChars > current_max);

        va_end(args);


        int ret = -1;

#ifdef LOG_OUTPUT_CONSOLE
        
        ret = fprintf(stderr, "%s%s\n", date_string_cons, arg_string);
        
#endif


#ifdef LOG_OUTPUT_FILE
        
        FILE *logFile = fopen(LOG_FILENAME, "a");

        if (logFile) {
            ret = fprintf(logFile, "%s%s\n", date_string_file, arg_string);

            fclose(logFile);
        } else {
            fprintf(stderr, "Couldn't open logfile, ignoring...");
        }

#endif
        
        return ret;
    }
    return 0;                                          
}

#else // Log DEBUG
int logm(const debug_lvl level, const char *str, ...) {
	return 0;
}

#endif // Log DEBUG
