
all: main format
	
main: W02 W02.h
	cc -o build/W02 W02.o -lX11

W02: W02.c W02.h
	cc -c W02.c -lX11 


format:
	clang-format -i *.c

clean:
	rm -rf *.o build/*

rebuild: clean all


