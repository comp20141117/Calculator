.PHONY: clean

OBJ = main.o Calculate.o Stack.o

express: $(OBJ)
	gcc -o $@ $(OBJ)

main.o: main.c Calculate.h
	gcc -o $@ -c $<

Calculate.o: Calculate.c Calculate.h Stack.h
	gcc -o $@ -c $<

Stack.o: Stack.c Stack.h
	gcc -o $@ -c $<

clean:
	rm $(OBJ)
	rm express
	rm *~
