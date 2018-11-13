#include "includes.h"
#include "Area.h"
#include "Sem-sv/sv_shm.h"
#include "Sem-sv/sv_sem.h"

int main(int argc, char* argv[]){

  if (argc<2){
    cerr<<"Faltan argumentos"<<endl;
    exit(1);
  }

  Area * a;
  sv_shm a51("Area51");
  a= static_cast <Area*>(a51.map(sizeof(Area)));
  sv_sem prod("A51p",5);
  sv_sem cons("A51c",0);
  
  string nombre = argv[1];
  cout<<"Poniendo "<<nombre<<endl;
  a->pone(Mensaje (nombre));  
  
  prod.wait();
  cons.post();

  if (argc >= 3) {
    a->setUltimo();
  }
  
  cout<<"Productor terminado"<<endl;
}

    
