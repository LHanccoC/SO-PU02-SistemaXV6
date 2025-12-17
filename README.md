### Integrantes
Néstor André Alarcón Luque (2023-119002)

Lizeth Hancco Calizaya	   (2023-119022)
### Descripción breve del proyecto.
Este proyecto permite implementar herramientas de monitoreo y control sobre las llamadas al sistema, al implementar nuevas funciones que faciliten la observación de la ejecución de los procesos sin alterarlos, el conteo de invocaciones por llamada al sistema
### Instrucciones para compilar y ejecutar.

1. Clonar el repositorio del sistema operativo modificado.

git clone https://github.com/LHanccoC/SO-PU02-SistemaXV6

2. Navegar al directorio del sistema.
 
cd SO-PU02-SistemaXV6/sistema

3. Compilar el sistema operativo con las nuevas modificaciones. 

make clean

make

make qemu

4. Ejecutar las nuevas herramientas implementadas

trace on 

trace off

psinfo

uptime

lsx

syscount <num_syscall>
