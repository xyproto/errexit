#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <getopt.h>

#define VERSION "1.0.1"

static void usage(void) {
    fprintf(stderr, "usage: errexit [OPTIONS] string [exit_code]\n");
    fprintf(stderr, "  -e, --error     prefix with 'error: '\n");
    fprintf(stderr, "  -E, --Error     prefix with 'Error: '\n");
    fprintf(stderr, "  -v, --version   show version\n");
    fprintf(stderr, "  -h, --help      show this help\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    const char *prefix = "";

    static struct option long_options[] = {
        {"error",   no_argument, 0, 'e'},
        {"Error",   no_argument, 0, 'E'},
        {"version", no_argument, 0, 'v'},
        {"help",    no_argument, 0, 'h'},
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

    fprintf(stderr, "%s%s\n", prefix, message);

    pid_t ppid = getppid();
    if (ppid > 1) {
        if (kill(ppid, SIGPIPE) != 0) {
            kill(ppid, SIGKILL);
        }
    }

    exit(1);
}
