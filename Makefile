
object =  bounce2d.o  block.o

bounce2d :	$(object)
	gcc $(object) -l curses -o bounce2d 

%.o : %.c
	gcc -c $<

.PHONY : clean
clean:
	rm *.o
	rm bounce2d