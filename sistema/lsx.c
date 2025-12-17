#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Encontrar el último componente de la ruta (el nombre del archivo)
    for(p=path+strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;
    // Copiar el nombre del archivo en un buffer temporal  
    if(strlen(p) >= DIRSIZ)
        return p;
    strcpy(buf, p);
    return buf;
}
void
ls(char *path)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    printf(2, "lsx: no se puede abrir %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf(2, "lsx: no se puede obtener estado de %s\n", path);
    close(fd);
    return;
  }

  printf(1, "Nombre Tipo Tamanio Inodo\n");
  switch(st.type){
  case T_FILE:
    printf(1, "%s %d %d %d\n", fmtname(path), st.type, st.size, st.ino);
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf(1, "ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf(1, "ls: cannot stat %s\n", buf);
        continue;
      }
      printf(1, "%s %d %d %d\n", fmtname(buf), st.type, st.size, st.ino);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    ls(".");
    exit();
  }
  for(i=1; i<argc; i++)
    ls(argv[i]);
  exit();
}