
all : prog
prog : main.o 
		gcc -o prog main.o -lm
		
main.o : main.c 
		gcc -o main.o -c main.c -lm

	 

ps:
		rm PID.txt time.txt
		touch PID.txt time.txt
		ps|cut -c3-7 >PID.txt
		ps|cut -c18-25 >time.txt

		

clean :
	rm -rf *.o *.bak

mrproper :clean
	rm -rf $(Exec)