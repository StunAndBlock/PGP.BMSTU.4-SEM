
all: xfloor format

xfloor: xfloor.c
	cc -o build/xfloor xfloor.c -lX11 

format:
	clang-format -i *.c

clean:
	rm -rf build/*

rebuild: clean all


