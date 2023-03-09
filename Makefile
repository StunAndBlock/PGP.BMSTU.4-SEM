.PHONY: format clean rebuild
BUILD=build/$(PROJ)

all:W21

xfloor: W13.c
	cc -o $(BUILD) W13/W13.c -lX11 

W21: W21_C winW21Handler_C INFORM_C format
	cc -o $(BUILD) W21.o winW21Handler.o inform.o -lX11 -g

W21_C:
	cc -c $(PROJ)/W21.c -g

winW21Handler_C: 
	cc -c $(PROJ)/winW21Handler.c -g

INFORM_C:
	cc -c $(PROJ)/inform.c -g

format:
	clang-format -i $(PROJ)/*.c $(PROJ)/*.h

clean:
	rm -rf $(BUILD) $(PROJ)/*.o

rebuild: clean all


