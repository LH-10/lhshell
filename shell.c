#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>

char **read_input(char*);

int main(){
	char **command=NULL;
	char *input;
	int status;
	while(1){
		input=readline("lhshell>");
		command=read_input(input);
		if (!command[0]){
			free(command);
			free(input);
		}
		pid_t child_pid=fork();
		if(child_pid==0){
			printf("debug:child created %d",getpid());
			execvp(command[0],command);

		}else{
			waitpid(child_pid, &status,WUNTRACED | WCONTINUED) ;

		}
		free(input);
		free(command);
	}
}


char **read_input(char *input){
	char **command=malloc(8* sizeof( char* ));
	char *arg=NULL;
	char *delimtr=" ";
	arg=strtok(input,delimtr);
	int indx=0;
	while(arg!=NULL){
		command[indx++]=arg;
		arg=strtok(NULL,delimtr);
	}
	command[indx]=arg;
	
	return command;
}
