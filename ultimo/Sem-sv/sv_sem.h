#include "includes.h"
#ifndef SV_SEM_H
#define SV_SEM_H

#if defined(_SEM_SEMUN_UNDEFINED)

union semun {
             int     val;            /* value for SETVAL */
             struct  semid_ds *buf;  /* buffer for IPC_STAT & IPC_SET */
             u_short *array;         /* array for GETALL & SETALL */
     };
#endif
class sv_sem{
    string clave;
    key_t ktclave;
    int sem;			//sem handler
    public:
        sv_sem(string cla="/default",int ini=1);
        void del();
        string getnom() {return clave;}
        int getsem()  {return sem;}
        key_t getKtClave(){return ktclave;}
        void post();
        void wait();
        friend ostream& operator <<(ostream& os, sv_sem sem);
 };

sv_sem::sv_sem(string cla,int ini){
    char * nom;
    int  oflag;
    int err;
    oflag = 0644 | IPC_CREAT;
    int oflag_excl=oflag|IPC_EXCL;
    if (cla[0] != '/') cla='/'+cla;
    clave="/tmp"+cla;
    string cmd="touch "+clave;
    system(cmd.c_str());         // en System V la clave DEBE ser un archivo
    ktclave=ftok(clave.c_str(),1);
    sem=semget(ktclave,1, oflag_excl);
    err=errno;
    if (sem==-1){
        if (errno==EEXIST){
            sem=semget(ktclave,1, oflag);
            if (sem==-1){
                cerr<<"no se puede abrir el semaforo"<<clave<<endl;
                exit(1);}
            }
        else {
             cerr<<"no se puede crear el semaforo"<<clave<<endl;
            exit (1);
             }
        }	
   else{
        int ret=semctl(sem, 0, SETVAL, ini); 
        if (ret==-1){
            cerr<<"no se puede inicializar el semaforo"<<clave<<
            " al valor "<<ini<<endl;
            }
        }
}
void sv_sem::del(){
    int retcode;
    retcode=semctl (sem, 0, IPC_RMID);
    if (retcode==-1){
 		cerr<<"No se puede cerrar el semaforo "<<endl;
		cerr<<"Semaforo<"<<clave<<","<<sem<<"> "<<endl; 
 		exit(1);}
    string cmd="rm "+clave;
    system (cmd.c_str());
}

void sv_sem::post(){
    int retcode;
    struct sembuf oper;
    oper.sem_num = 0; 		/* nro de semaforo */
    oper.sem_op = 1;			/* v(sem) */
    oper.sem_flg = 0;
    retcode=semop (sem, &oper, 1);
    if (retcode==-1){
     	perror ("No se puede hacer post al semaforo");
        cerr<<"Semaforo<"<<clave<<"> "<<endl; 
     	exit(1);}
}

void sv_sem::wait(){
    int retcode;
    struct sembuf oper;
    oper.sem_num = 0; 		/* nro de semaforo del set */
    oper.sem_op =  -1;		/* p(sem) */
    oper.sem_flg = 0;
    retcode=semop (sem, &oper, 1);
    if (retcode==-1){
 		perror ("No se puede hacer wait en el semaforo");
		cerr<<"Semaforo<"<<clave<<"> "<<endl; 
 		exit(1);}
}

ostream& operator << (ostream& os,sv_sem a)
{
     union semun arg;
     struct semid_ds seminfo;
     arg.buf=&seminfo;
     os<<"Semaforo  con Id "<<a.clave<<" y clave 0x"<<hex <<a.ktclave<<dec;
    if (semctl(a.sem,0,GETALL,arg)==-1)
            {return os<<"No puedo tomar el valor del semaforo \n";}
 	return os <<" con valor "<<arg.array[0]<<endl;
}
#endif

