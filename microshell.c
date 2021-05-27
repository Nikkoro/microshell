
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <sys/utsname.h>
/* sudo apt install libreadline-dev 
#include <readline/readline.h>
#include <readline/history.h> */

#define kreset   "\x1b[0m"
#define kblack	 "\x1b[30m"
#define kred     "\x1b[31m"
#define kgreen   "\x1b[32m"
#define kyellow  "\x1b[33m"
#define kblue    "\x1b[34m"
#define kmagenta "\x1b[35m"
#define kcyan    "\x1b[36m"
#define kwhite	 "\x1b[37m"
#define kbggreen "\x1b[42m"
#define kbgyell	 "\x1b[43m"

void start(){

	printf(kbgyell"----- MicroShell SOP -----" kreset);
	printf("\n");
	printf(kbggreen"Autor : Nikodem Domaracki" kreset);
	printf("\n");
	printf(kbgyell"Nr indeksu: s457992" kreset);
	printf("\n");
	printf(kbggreen"Wpisz 'help' by uzyskac informacje o projekcie" kreset);
	printf("\n");
}

void cm_help(){
	printf("\n");
	printf(kbgyell"Autor: Nikodem Domaracki" kreset);
	printf("\n");
	printf(kbggreen"Nr indeksu: s457992" kreset);
	printf("\n");
	printf(kbgyell"Dostepne polecenia: help, cd, exit"kreset);
	printf("\n");
	
}

struct utsname hostname;

void prompt() { 	
	char *user; 
	char dir[FILENAME_MAX];
	user = getenv("USER"); 	
	uname(&hostname);  
	getcwd(dir, sizeof(dir)); 
	printf(kgreen"[%s" kreset,user);
	printf(kyellow"@" kreset);
	printf(kgreen"%s:" kreset,hostname.nodename);
	printf(kyellow"%s]" kreset,dir);
	printf(kyellow"\n$ " kreset);
	
}

void cm_exit(){
	printf(kbgyell"Do zobaczenia!" kreset);
	printf("\n");
	exit(0);
}

#define arsize 100
#define insize 4096

void input(){
	char *argc[arsize];
	char *cmd;

	prompt();
	char uinput[insize];       
    char *delim = " \n";
    char *token;
	int argx = 0;

	if(fgets(uinput, insize, stdin) != 0){
		 
		for (token = strtok (uinput, delim);    
		        token && argx + 1 < arsize; 
		        token = strtok(NULL, delim)){
			    	argc[argx++] = token;
					cmd = argc[0];		
				}		
		}

		if (strcmp(cmd, "help") == 0)
			cm_help();
		else if (strcmp(cmd, "cd") == 0)
			chdir(argc[1]);
		else if (strcmp(cmd, "exit") == 0)
			cm_exit();
		
		else {
		  pid_t pid;
		  pid = fork();
		  	if ( pid == -1){
		  		printf("Proces potomny nie dziala\n"); 
		  		return;
		  	}
		   else if (pid == 0){
				if (execvp(cmd, argc)  < 0) {
					printf("Nie znaleziono polecenia\n");
					exit(0);
					
				}
			}				
			else 
				wait(NULL);
		}
		int i;
		for(i=1;i < arsize;i++)
		argc[i]= NULL;	

}

int main(){
	start();
	while(1) {
		input();
			
	}
	return 0;
}
