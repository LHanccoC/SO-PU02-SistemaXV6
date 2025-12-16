#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    int pid = fork();

    if(pid < 0){
        printf(2, "Fork failed\n");
        exit();
    }

    if(pid == 0){
        // Proceso hijo
        printf(1, "Hijo: durmiendo 5 ticks\n");
        sleep(5);
        printf(1, "Hijo: terminado\n");
        exit();
    } else {
        // Proceso padre
        printf(1, "Padre: esperando a hijo\n");
        wait();
        printf(1, "Padre: hijo termina\n");
    }

    exit();
}

