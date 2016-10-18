object = more.o term.o file_cfg.o screen.o who.o showTime.o

main : $(object) 
	gcc -o main $(object) 

more.o : ../inc/more.h 
term.o : ../inc/term.h
file_cfg.o : ../inc/file_cfg.h
screen.o : ../inc/screen.h
who.c :	../inc/who.h
showTime.c : ../inc/showTime.h

.PHONY : clean
clean : 
	-rm $(object)  
