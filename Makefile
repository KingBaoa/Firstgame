
object =  bounce2d.o 

bounce2d :	$(object)
	gcc $(object) -l curses -o bounce2d

%.o : %.curses
	gcc -c $<

.PHONY : clean
clean:
	rm *.o
	rm bounce2d