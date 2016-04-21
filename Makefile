.PHONY: clean

OBJ = main.o calculate.o stack.o button.o display.o

calculate: $(OBJ)
	gcc -o $@ $(OBJ) -lSDL2 -lSDL2_ttf

main.o: main.c calculate.h button.h display.h global.h
	gcc -o $@ -c $<

calculate.o: calculate.c calculate.h stack.h
	gcc -o $@ -c $<

stack.o: stack.c stack.h
	gcc -o $@ -c $<

button.o: button.c button.h
	gcc -o $@ -c $<

display.o: display.c display.h button.h
	gcc -o $@ -c $<

clean:
	rm $(OBJ)
	rm calculate
	rm *~
