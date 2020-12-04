main:
	# Make the library
	g++ -c util.cpp
	ar -cvq libutil.a util.o

	# Make the prog
	g++ -c -I. main.cpp
	g++ -o main main.o -L. -lutil

clean:
	rm *.o
	rm *.a
	rm main
