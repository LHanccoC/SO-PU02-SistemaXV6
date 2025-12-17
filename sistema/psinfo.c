#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h" // Para NPROC

int main(int argc, char *argv[])
{
    struct procinfo pinfos[NPROC];
    int num_procs;

    // Llama a la syscall, pasa el buffer y recibe el número de procesos
    num_procs = getprocinfo(pinfos);

    if (num_procs < 0)
    {
        printf(2, "Error al obtener la información de los procesos\n");
        exit();
    }
    // Imprime la información en formato tabla
    printf(1, "PID | Estado | CambiosCtx | TamanioMem\n");
    printf(1, "-----------------------------------------------\n");

    for (int i = 0; i < num_procs; i++)
    {
        printf(1, "%d | %s | %d | %d\n",
               pinfos[i].pid,
               pinfos[i].state_name,
               pinfos[i].context_switches,
               pinfos[i].sz);
    }

    exit();
}
