#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>
#include "colors.h"
#include <readline/readline.h>
#define PATH_SIZE 100

static sigjmp_buf env;

void signal_handler(int signo){
	siglongjmp(env,35);
}

int change_cwd_text(char *display_text,size_t display_text_size){

	char current_dir[PATH_SIZE];
	if(!getcwd(current_dir, PATH_SIZE)){
		return -1;
	}

	int ret_val = append_colored_text(display_text, display_text_size, C_YELLOW, current_dir) ;
	if (ret_val < 0) {return ret_val;}
	return append_colored_text(display_text, display_text_size, C_RESET, "# ") ;
	
	
}

char **read_input(char*);

int main(){
	char **command=NULL;
	char *input;
	int status;

	
	char display_text[190];
	int sns=make_colored_text(display_text,sizeof(display_text),C_CYAN,"lhshell:") ;
	if (sns < 0){
		printf("error while making text");
		return 0;
	}
	size_t shell_name_size=sizeof("\033[36mlhshell:\033[0m\033[33m");
	if( change_cwd_text(display_text,190) < 0 ){
		printf("cwd error");
	}
	signal(SIGINT,signal_handler);
		
	while(1){
	
		if(sigsetjmp(env,1)==35){
			printf("\n");
		}	

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
			display_text[sns]='\0';

			if( change_cwd_text(display_text,sizeof(display_text)) < 0 ){
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
