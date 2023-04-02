.PHONY: format clean rebuild
BUILD=build/$(PROJ)

all:W21

xfloor: W13.c
	cc -o $(BUILD) W13/W13.c -lX11 

W21: W21_C winW21Handler_C INFORM_C envW21Handler_C format
	cc -o $(BUILD) W21.o winW21Handler.o envW21Handler.o inform.o -lX11 -g

W21_C:
	cc -c $(PROJ)/W21.c -g

winW21Handler_C: 
	cc -c $(PROJ)/winW21Handler.c -g
envW21Handler_C:
	cc -c $(PROJ)/envW21Handler.c -g

W23: W23_C winW23Handler_C envW23Handler_C format
	cc -o $(BUILD) W23.o winW23Handler.o envW23Handler.o -lX11 -g

W23_C:
	cc -c $(PROJ)/W23.c -g

winW23Handler_C: 
	cc -c $(PROJ)/winW23Handler.c -g
envW23Handler_C:
	cc -c $(PROJ)/envW23Handler.c -g



INFORM_C:
	cc -c $(PROJ)/inform.c -g

W07: W07_C winW07Handler_C numW07Handler_C format
	cc -o $(BUILD) W07.o winW07Handler.o numW07Handler.o -lX11 -g
W07_C:
	cc -c $(PROJ)/W07.c -g

winW07Handler_C: 
	cc -c $(PROJ)/winW07Handler.c -g


numW07Handler_C:
	cc -c $(PROJ)/numW07Handler.c -g


W28: W28.o winW28Handler.o envW28Handler.o inform.o format
	cc -o $(BUILD) W28.o winW28Handler.o envW28Handler.o inform.o -lX11 -g

W28.o: $(PROJ)/W28.c
	cc -c $(PROJ)/W28.c -g

winW28Handler.o: $(PROJ)/winW28Handler.c
	cc -c $(PROJ)/winW28Handler.c -g
envW28Handler.o:$(PROJ)/envW28Handler.c 
	cc -c $(PROJ)/envW28Handler.c -g




24S: 24S.o win24SHandler.o env24SHandler.o inform.o format
	cc -o $(BUILD) 24S.o win24SHandler.o env24SHandler.o inform.o -lX11 -g

24S.o: $(PROJ)/24S.c
	cc -c $(PROJ)/24S.c -g

win24SHandler.o: $(PROJ)/win24SHandler.c
	cc -c $(PROJ)/win24SHandler.c -g
env24SHandler.o:$(PROJ)/env24SHandler.c 
	cc -c $(PROJ)/env24SHandler.c -g

#-------------------------------------------------------------------end



inform.o: $(PROJ)/inform.c
	cc -c $(PROJ)/inform.c -g


format:
	clang-format -i $(PROJ)/*.c $(PROJ)/*.h


clean:
	rm -rf $(BUILD) *.o

rebuild: clean all


