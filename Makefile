
all: main format
	
main: W02 W02HANDLER WINDOWHANDLER W02.h
	cc -o build/W02 W02.o w02Handler.o windowHandler.o -lX11 -g



W02: W02.c W02.h
	cc -c W02.c -lX11 -g

WINDOWHANDLER: windowHandler.c W02.h
	cc -c  windowHandler.c -lX11 -g

W02HANDLER: w02Handler.c W02.h
	cc -c w02Handler.c -lX11 -g

format:
	clang-format -i *.c

clean:
	rm -rf *.o build/*

rebuild: clean all


