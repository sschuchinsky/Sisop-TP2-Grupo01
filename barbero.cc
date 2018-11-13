#include  "Sem-sv/sv_sem.h"
#include  "Sem-sv/sv_shm.h"
#include  "Mensaje.h"
#include  "portada.h"
using namespace std;

int main(){

    portada();
    
    sv_sem cliente ("cliente",0);
    sv_sem barbero ("barbero",0);

    Mensaje * msj;
    sv_shm area("area");
    msj=reinterpret_cast<Mensaje *> (area.map(BUFSIZ));
    while (!msj->esUltimo()){
        cout<<"Barbero listo"<<endl;
        cin.ignore();
        barbero.post();
        cout<<"Esperando cliente"<<endl;
        cin.ignore();
        cliente.wait();
        cout<<"Atendiendo a "<<msj->getDato()<<endl;
        cin.ignore();
        cout<<"Corte finalizado"<<endl;
        cin.ignore();
    }
    cliente.del();
    barbero.del();
    area.del();
}
