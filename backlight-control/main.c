#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>


#include "argparse.h"


#define MAX_BRIGHTNESS "/sys/class/backlight/ideapad/max_brightness" // Change
#define BRIGHTNESS "/sys/class/backlight/ideapad/brightness"         // these
#define MAX_DIGITS 5
#define INIT INT_MAX


static const char *const usage[] = {
    "backlightctl [options] [[--] args]",
    "backlightctl [options]",
    NULL,
};



int
main(int argc, const char **argv) {

    int verbose = 0;
    int inc_amount = INIT, dec_amount = INIT;

    int actual_fd, max_fd, maxval;
    register int i, n, val;
    char buff[16];

    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_BOOLEAN('v', "verbose", &verbose, "verbose mode"), 
        OPT_INTEGER('i', "inc", &inc_amount, "increase brightness by a certain amount"), 
        OPT_INTEGER('d', "dec", &dec_amount, "decrease brightness by a certain amount"), 
        OPT_END(),
    };

    struct argparse argparse;
    argparse_init(&argparse, options, usage, 0);
    argparse_describe(&argparse, "\nA utility to get and modify screen backlight brightness", "\nWritten with <3 by b3h3m0th");
    argc = argparse_parse(&argparse, argc, argv);



    actual_fd = open(BRIGHTNESS, O_RDWR);
    max_fd = open(MAX_BRIGHTNESS, O_RDONLY);

    read(actual_fd, buff, MAX_DIGITS);
    n = strlen(buff); i = 0;
    while(i < n && isdigit(buff[i])) i++;
    buff[i] = '\0';
    val = atoi(buff);


    read(max_fd, buff, MAX_DIGITS);
    n = strlen(buff); i = 0;
    while(i < n && isdigit(buff[i])) i++;
    buff[i] = '\0';
    maxval = atoi(buff);
    close(max_fd);



    if(inc_amount != INIT && dec_amount != INIT) {
        printf("\n [!] multiple actions specified while expecting one\n");
        return -1;
    }


    if(inc_amount == INIT && dec_amount == INIT) {
        printf("%d", val);
        return 0;
    }


    if(inc_amount != INIT) {
        val = val + inc_amount;
    }

    if (dec_amount != INIT){
        val = val - dec_amount;
    }


    if(val < 0) val = 0;
    if(val > maxval) val = maxval;

    if(val == 0) {
        write(actual_fd, "0", 1);
        close(actual_fd);
        printf("0");
        return 0;
    }


    snprintf(buff, MAX_DIGITS, "%d", val);
    n = strlen(buff); i = 0;
    while(i < n && isdigit(buff[i])) i++;
    buff[i] = '\0';
    write(actual_fd, buff, i);
    printf("%d", val);
    close(actual_fd);
    return 0;
}
