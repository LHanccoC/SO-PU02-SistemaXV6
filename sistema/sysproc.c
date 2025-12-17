#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h" 

extern int syscall_count[];

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int 
sys_trace(void) 
{
    int on;
    
    if (argint(0, &on) < 0)
        return -1;
    myproc()->tracing = on;
    return 0;
}

int
sys_getsyscount(void)
{
  int num;

  if(argint(0, &num) < 0)
    return -1;

  if(num < 0 || num >= 32)
    return -1;

  return syscall_count[num];
}

// Estructura para transferir la información de un proceso al espacio de usuario
struct procinfo {
  int pid;
  char state_name[16]; 
  int context_switches;
  int sz; 
};

struct sys_stats {
    uint ticks;
    int active_procs;
};

// Definición del ptable para acceder a la tabla de procesos
extern struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

static char *states[] = {
  [UNUSED]    "unused",
  [EMBRYO]    "embryo",
  [SLEEPING]  "sleeping",
  [RUNNABLE]  "runnable",
  [RUNNING]   "running",
  [ZOMBIE]    "zombie"
};

// Nueva syscall para obtener información de los procesos
int
sys_getprocinfo(void)
{
  struct procinfo *u_pinfos; // Puntero al array de structs en espacio de usuario
  struct proc *p;
  int i = 0;

  // Obtener el puntero al array de structs desde los argumentos de la syscall
  if (argptr(0, (char**)&u_pinfos, sizeof(struct procinfo) * NPROC) < 0)
    return -1;
  
  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state != UNUSED){
      // Llenar la estructura de información del proceso
      struct procinfo k_pinfo;
      k_pinfo.pid = p->pid;
      k_pinfo.context_switches = p->context_switches;
      k_pinfo.sz = p->sz;
      safestrcpy(k_pinfo.state_name, states[p->state], 16);

      // Copiar la estructura al espacio de usuario
      if(copyout(myproc()->pgdir, (uint)&u_pinfos[i], (char*)&k_pinfo, sizeof(k_pinfo)) < 0) {
        release(&ptable.lock);
        return -1;
      }
      i++;
    }
  }
  release(&ptable.lock);
  return i; // Retorna el número de procesos activos copiados
}
