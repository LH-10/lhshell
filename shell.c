#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>
#define PATH_SIZE 100

int change_cwd_text(char *display_text){

	char current_dir[PATH_SIZE];
	if(!getcwd(current_dir,PATH_SIZE)){
		return -1;
	}

	if(!strcat(display_text,strcat(current_dir,"# "))){
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

	
	char display_text[90]="lhshell";
	if(!(change_cwd_text(display_text)+1)){
		printf("cwd error");
	}
	while(1){
		input=readline(display_text);
		command=read_input(input);
		if (!command[0]){
			free(command);
			free(input);
		}
		if (strcmp(command[0],"cd")==0){
			chdir(command[1]);
			free(command);
			free(input);
			memcpy(display_text,"lhshell",8*sizeof(char));	
			if(!(change_cwd_text(display_text)+1)){
				printf("cwd error");
			}		
			continue;				
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
