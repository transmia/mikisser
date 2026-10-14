#include <stdio.h>
#define NOB_IMPLEMENTATION
#include "./thirdparty/nob.h"

static char* program;

int main(int argc, char** argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);

    program = shift(argv, argc);

    Cmd cmd = {0};

    cmd_append(&cmd, 
        "gcc", 
        "./source/main.c",
        "-I", "./emulator/include",
        "-c", "-o", "./firmware.o"
    );

    if (!cmd_run(&cmd)) {
        printf("Error running command\n");
        return 1;
    }

    cmd_append(&cmd, 
        "gcc", 
        "./emulator/main.c",
        "./lib/libraylib.a",
        "./firmware.o",
        "-lopengl32", "-lgdi32", 
        "-lm", "-luser32",
        "-lwinmm",
        "-o", "./emulator"
    );

    if (!cmd_run(&cmd)) {
        printf("Error running command\n");
        return 1;
    }

    char* subcommand = shift(argv, argc);

    if (subcommand) {
        if (strcmp(subcommand, "run") == 0) {
            cmd_append(&cmd,
                #if defined(_WIN32)
                "./emulator.exe"
                #else
                "./emulator"
                #endif
            );
            if (!cmd_run(&cmd)) {
                printf("Error running command\n");
                return 1;
            }
        } else {
            printf("Unknown subcommand: %s\n", subcommand);
        }
    }

    return 0;
}