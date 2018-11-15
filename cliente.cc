#include  "Sem-sv/sv_sem.h"
#include  "Sem-sv/sv_shm.h"
#include  "Area.h"
#include  "portada.h"
using namespace std;

int main(int argc, char * argv[]){

    portada();
    
    if (argc<2){
        cerr<<"Faltan argumentos"<<endl;
        exit(1);
    }

    sv_sem cliente ("cliente",0);
    sv_sem barbero ("barbero",0);
  
   Area * a;
   sv_shm area("area");
   a=reinterpret_cast<Area *> (area.map(BUFSIZ));
    
    cout<<argv[1]<<" entra a sala de espera, presione enter para continuar.."<<endl;
    cin.ignore();
    cliente.post();
    cout<<argv[1]<<" esperando al barbero"<<endl;
    barbero.wait();
    cout<<"Barbero listo, ingresa "<<argv[1]<<endl;

     if (argc>=3){
	a->setUltimo();
    }

}
