#include  "Sem-sv/sv_sem.h"
#include  "Sem-sv/sv_shm.h"
#include  "Mensaje.h"
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
    
    Mensaje * msj;
    sv_shm area("area");
    msj=reinterpret_cast<Mensaje *> (area.map(BUFSIZ));
    msj->setDato(argv[1]);
    
    cout<<argv[1]<<" entra a sala de espera, sigo?"<<endl;
    cin.ignore();
    cliente.post();
    cout<<"Esperando al barbero"<<endl;
    cin.ignore();
    barbero.wait();
    cout<<"Barbero listo, ingresa "<<argv[1]<<endl;

     if (argc>=3){
        msj->setUltimo();
    }

}
