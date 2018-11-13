#include "includes.h"
#ifndef SV_SHM_H
#define SV_SHM_H
#define BUFSIZE 8192

class sv_shm{
    string clave; 
    int shm;
    key_t ktclave;
    public:
        sv_shm(string cla="/default");
        void del();
        int getShm(){return shm;}
        key_t getKtClave(){return ktclave;}
        void * map(int size=BUFSIZE);  // size esta por compatibilidad con las posix. Se usa BUFSIZE
        string getClave(){return clave;}
};

sv_shm::sv_shm(string cla){
    int	c, oflag;
    size_t	length=BUFSIZE;
    oflag=IPC_CREAT|0644;
    if (cla[0] != '/') cla='/'+cla;
    clave="/tmp"+cla;
    string cmd="touch "+clave;
    system(cmd.c_str());         // en System V la clave DEBE ser un archivo
    ktclave=ftok(clave.c_str(),1);	
    shm = shmget(ktclave, length, oflag);
    if(shm==-1){
        cerr<<"no se puede crear/acceder a la shm "<<clave<<endl;
        exit(1);
    }
}

void sv_shm::del(){
    int ret;
    ret=shmctl(shm, IPC_RMID, NULL);
    if (ret==-1){
        cerr<<"no se puede destruir la shm "<<clave<<endl;
        exit(1);
    }
    string cmd="rm "+clave;
    system (cmd.c_str());
}

void * sv_shm::map(int size){
    void * addr;
    void * menos_uno=reinterpret_cast<void *> (-1);
    addr=shmat(shm, NULL, 0);
    if (addr==menos_uno){
        cerr<<"no se puede mapear la shm "<<clave<<endl;
        exit(1);
    }
   return addr;
}
#endif