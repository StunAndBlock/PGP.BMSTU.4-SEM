
all: W13 format

xfloor: W13.c
	cc -o build/W13 W13/W13.c -lX11 

format:
	clang-format -i W13/*.c

clean:
	rm -rf build/*

rebuild: clean all


