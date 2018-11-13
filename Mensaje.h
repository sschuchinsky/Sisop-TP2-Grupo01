#ifndef Mensaje_h
#define Mensaje_h
using namespace std;
class Mensaje{
	bool ultimo;
	char dato [40];
	public:
		Mensaje() {
			strcpy (dato,"");
			ultimo=false;
			}
		Mensaje(string d) {
			strcpy (dato,d.c_str());
			ultimo=false;
			}
		Mensaje (const Mensaje & m){
			strcpy(dato,m.dato);
			ultimo=false;
			}
		string getDato(){return dato;};
		void setDato(string d){
		  strcpy (dato,d.c_str());
		  ultimo=false;
		}
		
		void setUltimo(){ultimo=true;};
		bool esUltimo(){return ultimo;};
	
		friend ostream& operator<<(ostream& os, Mensaje m){
			os<<"("<<m.getDato();
			if (m.esUltimo()) os<<", ultimo";
			return os<<")";
			} 
};
#endif
