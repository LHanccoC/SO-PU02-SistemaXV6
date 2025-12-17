#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    struct sys_stats stats;
    int res;

    res = getsysstats(&stats);

    if (res < 0)
    {
        printf(2, "Error al obtener las estadísticas del sistema\n");
        exit();
    }

    uint seconds = stats.ticks / 100;

    printf(1, "Tiempo de actividad del sistema: %d segundos\n", seconds);
    printf(1, "Numero de ticks del sistema: %d\n", stats.ticks);
    printf(1, "Numero de procesos activos: %d\n", stats.active_procs);
    printf(1, "Total de cambios de contexto en el sistema: %d\n", stats.total_switches);

    exit();
}
