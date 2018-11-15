#include "Sem-sv/sv_sem.h"
#include "Sem-sv/sv_shm.h"
#include <iostream>
#include  "portada.h"
using namespace std;

int main(){

    portada();
    
	sv_sem cliente ("cliente",0);
	cout<<"Semaforo cliente inicializados"<<endl;
	sv_sem barbero ("barbero",0);
	cout<<"Semaforo barbero inicializados"<<endl;
        sv_shm area("area");
	cout<<"Area compartida inicializada"<<endl;
}
