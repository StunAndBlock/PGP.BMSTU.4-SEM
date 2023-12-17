NAME=custom
BUILDFOLDER=build
global:all
all: main environment calculations
	gcc -o ./${NAME} main.o w_environment.o l_calculations.o -lX11 

main: main.c g_environment-class.h
	gcc -c main.c -lX11

environment: w_environment.c g_environment-class.h w_environment-definitions.h g_configurations.h 
	gcc -c w_environment.c -lx11

calculations: l_calculations.c l_calculations-definitions.h g_configurations.h 
	gcc -c l_calculations.c

rebuild: clean all

clean:
	rm *.o ./${NAME}
