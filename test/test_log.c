#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../src/util/logging.h"

//#include "../src/util/logging.c"

void test_log_output_file();
void test_log_output_console();

int main(int argc, char *args[]) {
    printf("Testing Logm module\n");
/*
#ifndef LOG_DEBUG
    printf("Logging not enabled. There is no code to be tested\n");
    return 0;
#endif*/

//#ifdef LOG_OUTPUT_FILE
    printf("Output file for logging enabled, testing the functionality\n");
    test_log_output_file();
//#endif

//#ifdef LOG_OUTPUT_CONSOLE
    printf("Output file for logging enabled, testing the functionality\n");
    test_log_output_console();
//#endif
    

    exit(0);
}

void test_log_output_console() {
    printf("Debug info:\n");
    logm(DEBUG_INFO, "Some Text");
    logm(DEBUG_INFO, "Some number: %d, and a string: \"%s\"", 3, "The String!");

}

void test_log_output_file() {
    logm(DEBUG_INFO, "Is this in the file?");
}
