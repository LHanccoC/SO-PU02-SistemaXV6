#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    int i;

    if(argc == 2) {
        int num = atoi(argv[1]);
        printf(1, "Syscall %d : %d invocaciones\n", num, getsyscount(num));
        exit();
    }

    printf(1, "Syscall counts:\n");
    for(i = 0; i < 24; i++) {
        printf(1, "Syscall %d: %d\n", i, getsyscount(i));
    }

    exit();
}

