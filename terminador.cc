#include  "Sem-sv/sv_sem.h"
#include  "Sem-sv/sv_shm.h"
#include  "portada.h"
using namespace std;

int main(){

    portada();

    sv_sem cliente ("cliente",0);
    sv_sem barbero ("barbero",0);
    sv_shm area("area");
    cliente.del();
	cout<<"Semaforo cliente borrado"<<endl;
    barbero.del();
	cout<<"Semaforo barbero borrado"<<endl;
    area.del();
	cout<<"Area compartida borrada"<<endl;
}
