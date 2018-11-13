CXXFLAGS=-std=c++11
LOADLIBES=-pthread #-lrt

todos= productor consumidor libera

productor:includes.h Mensaje.h  Area.h productor.cc
	g++ productor.cc ${LOADLIBES} -o productor

consumidor:includes.h Mensaje.h Area.h consumidor.cc
	g++ consumidor.cc ${LOADLIBES} -o consumidor
	
all: ${todos}

clean:
	rm -f ${todos} *~ 