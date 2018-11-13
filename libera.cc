#include "includes.h"
#include "Area.h"
#include "Sem-sv/sv_shm.h"
#include "Sem-sv/sv_sem.h"

int main(){
  sv_shm a51("Area51");
  sv_sem prod("A51p",5);
  sv_sem cons("A51c",0);
  a51.del();
  prod.del();
  cons.del();
}
