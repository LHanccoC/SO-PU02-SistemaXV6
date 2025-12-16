#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if(argc < 2 || (strcmp(argv[1], "on") != 0 && strcmp(argv[1], "off") != 0)) {
        printf(2, "Uso: trace on | off\n");
        exit();
    }
    if(strcmp(argv[1], "on") == 0){
        trace(1);
    }else{
        trace(0);
    }
    exit();
}
