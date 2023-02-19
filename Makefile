
all: pyramid format

pyramid: pyramid0.o pyramid1.o pyramid2.o 
	cc -o build/pyramid pyramid0.o pyramid1.o pyramid2.o -lX11 

pyramid0.o: pyramid0.c polyhedron.h
	cc -c pyramid0.c -lX11

pyramid1.o: pyramid1.c polyhedron.h
	cc -c pyramid1.c -lX11

pyramid2.o: pyramid2.c polyhedron.h
	cc -c pyramid2.c -lX11


format:
	clang-format -i *.c *.h

clean:
	rm -rf *.o build/*

rebuild: clean all


