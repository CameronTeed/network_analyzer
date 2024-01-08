objects = main.o Socket.o View.o Model.o Controller.o

main: $(objects)
	g++ -o main $(objects)

main.o: main.cpp
	g++ -c main.cpp

socket.o: Socket.cpp
	g++ -c Socket.cpp

View.o: View.cpp	
	g++ -c View.cpp

Model.o: Model.cpp	
	g++ -c Model.cpp

Controller.o: Controller.cpp	
	g++ -c Controller.cpp	


clean: 
	rm -f ./main ./output.txt $(objects)