#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <getopt.h>

#define VERSION "1.0.0"

static void usage(void) {
    fprintf(stderr, "usage: errexit [OPTIONS] string [exit_code]\n");
    fprintf(stderr, "  -e, --error     prefix with 'error: '\n");
    fprintf(stderr, "  -E, --Error     prefix with 'Error: '\n");
    fprintf(stderr, "  -h, --help      show this help\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    const char *prefix = "";
    
    static struct option long_options[] = {
        {"error", no_argument, 0, 'e'},
        {"Error", no_argument, 0, 'E'},
        {"help",  no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };
    
    int opt;
    while ((opt = getopt_long(argc, argv, "eEvh", long_options, NULL)) != -1) {
        switch (opt) {
        case 'e':
            prefix = "error: ";
            break;
        case 'E':
            prefix = "Error: ";
            break;
        case 'v':
            printf("errexit " VERSION "\n");
            exit(0);
            break;
        case 'h':
            usage();
            break;
        default:
            usage();
        }
    }
    
    if (optind >= argc) {
        usage();
    }
    
    const char *message = argv[optind];
    int exit_code = 1;
    
    if (optind + 1 < argc) {
        char *endptr;
        exit_code = (int)strtol(argv[optind + 1], &endptr, 10);
        if (*endptr != '\0') {
            fprintf(stderr, "errexit: invalid exit code\n");
            exit(1);
        }
    }
    
    fprintf(stderr, "%s%s\n", prefix, message);
    
    pid_t ppid = getppid();
    if (ppid > 1) {
        if (kill(ppid, SIGTERM) != 0) {
            kill(ppid, SIGKILL);
        }
    }
    
    exit(exit_code);
}
