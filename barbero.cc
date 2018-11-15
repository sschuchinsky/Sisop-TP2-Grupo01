#include  "Sem-sv/sv_sem.h"
#include  "Sem-sv/sv_shm.h"
#include  "Area.h"
#include  "portada.h"
using namespace std;

int main(){

    portada();
    
    sv_sem cliente ("cliente",0);
    sv_sem barbero ("barbero",0);

 
    Area * a;
    sv_shm area("area");
    a=reinterpret_cast<Area *> (area.map(BUFSIZ));

    while (!a->esUltimo()){
  
	cout<<"Barbero listo"<<endl;
	barbero.post();
        cout<<"Esperando cliente"<<endl;
	cin.ignore();
        cliente.wait();
        cout<<"Atendiendo cliente "<<a->getDato()<<endl;
	cout<<"Terminar corte?"<<endl;
        cin.ignore();
        cout<<"Corte finalizado"<<endl;
	cout<<"Sigo con el proximo cliente?"<<endl;
        cin.ignore();
    }
    
    cout<<"Ultimo cliente atendido"<<endl;
    cout<<"Puedo volver a dormir"<<endl;

    cliente.del();
    barbero.del();
    area.del();
}
