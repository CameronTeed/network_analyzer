objects = main.o Socket.o View.o Model.o Controller.o
testObjects = Tester.o Socket.o View.o Model.o Controller.o

main: $(objects)
	g++ -o main $(objects)

testmake: $(testObjects)
	g++ -o tester $(testObjects) -lgtest -lgtest_main

run:
	sudo python3 ./test.py

test:
	sudo ./tester

main.o: main.cpp
	g++ -c main.cpp 

socket.o: Socket.cpp
	g++ -c Socket.cpp

View.o: View.cpp	
	g++ -c View.cpp

Model.o: Model.cpp 
	g++ -c Model.cpp

Controller.o: Controller.cpp Controller.h
	g++ -c Controller.cpp


clean: 
	rm -f ./main ./output.txt ./tester $(objects)