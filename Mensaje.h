#ifndef Mensaje_h
#define Mensaje_h
class Mensaje{
	bool ultimo;
	char dato [40];
	public:
		Mensaje() {
			strcpy (dato,"");
			ultimo=false;
			}
		Mensaje(std::string d) {
			strcpy (dato,d.c_str());
			ultimo=false;
			}
		Mensaje (const Mensaje & m){
			strcpy(dato,m.dato);
			ultimo=false;
			}
		std::string getDato(){return dato;};
		void setDato(std::string d){
		  strcpy (dato,d.c_str());
		  ultimo=false;
		}
		
		void setUltimo(){ultimo=true;};
		bool esUltimo(){return ultimo;};
	
		friend std::ostream& operator<<(std::ostream& os, Mensaje m){
			os<<"("<<m.getDato();
			if (m.esUltimo()) os<<", ultimo";
			return os<<")";
			} 
};
#endif
