#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>
#define PATH_SIZE 100

char **read_input(char*);

int main(){
	char **command=NULL;
	char *input;
	int status;
	printf("here");
	char *current_dir=malloc(PATH_SIZE*sizeof(char ) );

	printf("here");
	
	getcwd(current_dir,PATH_SIZE);
	
	char display_text[40]="lhshell";
	if(!strcat(display_text,strcat(current_dir," >"))){
		printf("concat fail");
		if(current_dir!=NULL)
		free(current_dir);
		return 1;
	}
	while(1){
		input=readline(display_text);
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
	free(current_dir);
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
