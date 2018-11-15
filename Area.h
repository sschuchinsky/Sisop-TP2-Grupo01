#ifndef Area_h
#define Area_h
class Area{
	bool ultimo;
	char dato [40];
	public:
		Area() {
			strcpy (dato,"");
			ultimo=false;
			}
		std::string getDato(){return dato;};
		void setDato(std::string d){
		  strcpy (dato,d.c_str());
		  ultimo=false;
		}
		
		void setUltimo(){ultimo=true;};
		bool esUltimo(){return ultimo;};
};
#endif