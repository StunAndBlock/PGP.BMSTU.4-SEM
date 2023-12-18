NAME=custom
BUILDFOLDER=build
global:all
all: main environment calculations
	gcc -o ./${NAME} main.o w_environment.o l_calculations.o -lX11 -lm -g

main: main.c g_environment-class.h
	gcc -c main.c -g

environment: w_environment.c g_environment-class.h w_environment-definitions.h g_configurations.h 
	gcc -c w_environment.c -g

calculations: l_calculations.c l_calculations-definitions.h g_configurations.h 
	gcc -c l_calculations.c -g

rebuild: clean all

clean:
	rm *.o ./${NAME}
