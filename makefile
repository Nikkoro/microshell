
microshell: microshell.c
	gcc -Wall -ansi -o microshell microshell.c -L/usr/local/lib -I/usr/local/include -lreadline

clean:
	rm -f *.o microshell