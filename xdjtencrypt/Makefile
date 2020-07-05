main3: main3.o
	g++ -o c2 main3.o   /usr/lib/x86_64-linux-gnu/libgmp.a /usr/lib/x86_64-linux-gnu/libgmpxx.a
main3.o : main3.cpp
	g++ -Wall -fexceptions -g  -c main3.cpp -o main3.o
clean:
	rm main3.o -rf
