#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#define PATH_SIZE 100

int change_cwd_text(char *display_text){

	char current_dir[PATH_SIZE];
	if(!getcwd(current_dir,PATH_SIZE)){
		return -1;
	}

	if(!strcat(display_text,strcat(current_dir,"\033[0m# "))){
		printf("concat fail");
		return -1;
	}
	return 1;
}

char **read_input(char*);

int main(){
	char **command=NULL;
	char *input;
	int status;

	
	char display_text[90]="\033[36mlhshell:\033[0m\033[33m";
	size_t shell_name_size=sizeof("\033[36mlhshell:\033[0m\033[33m");
	if( change_cwd_text(display_text) < 0 ){
		printf("cwd error");
	}
	signal(SIGINT,SIG_IGN);
		
	while(1){
		
		input=readline(display_text);
		command=read_input(input);
		if (!command[0]){
			free(command);
			free(input);
			continue;
		}
		if (strcmp(command[0],"exit")==0) {
			free(command);
			free(input);
			break;
		}
				
		if (strcmp(command[0],"cd")==0){
			if( chdir(command[1]) < 0 ) {
				printf("error while changing directory");	
			}
			free(command);
			free(input);
			memcpy(display_text,"\033[36mlhshell:\033[0m\033[33m",shell_name_size);	
			if( change_cwd_text(display_text) < 0 ){
				printf("cwd error");
			}		
			continue;				
		}
		pid_t child_pid=fork();
		if(child_pid==0){
			signal(SIGINT,SIG_DFL);
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
