objects = main.o

main: $(objects)
	g++ -o main $(objects)

main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm -f main $(objects)