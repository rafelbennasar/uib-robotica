
CXFLAGS = -c -pedantic -Wall
CLIB = -I/usr/local/Aria/include 
LLIB = -L/usr/local/Aria/lib 
LFLAGS = -Llib  -lAria -lpthread -ldl -Xlinker -Bstatic -lstdc++ -Xlinker -Bdynamic -lm
source = main
worlddir= worlds
OBJECTS = robot.o hash.o sequencial.o conf.o bitmap.o

%.o:
	$(CXX) $*.cpp $(CXFLAGS) $(CLIB)

all: $(OBJECTS)

	$(CXX) -pedantic -Wall $(OBJECTS) $(source).cpp -o $(source) $(CLIB) $(LLIB) $(LFLAGS)
	mv *.o Objects

.PHONY: clean

clean: 
	rm *.o main


view:
	gthumb mapa.bmp

run:
	SRIsim -w $(worlddir)/peter.wld &


	sleep 1
	./$(source)
