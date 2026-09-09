#include "colors.h"
#include <stdio.h>
#include <stdlib.h>

const char C_RED[]="\033[31m";
const char C_BLUE[]="\033[34m";
const char C_YELLOW[]="\033[33m";
const char C_GREEN[]="\033[32m";
const char C_CYAN[]="\033[36m";
const char C_MAGENTA[]="\033[95m";
const char C_RESET[]="\033[0m";

int  make_colored_text(char buf[], size_t bufsize,const char color[],const char text[]){
	
	snprintf(buf,bufsize,"%s%s",color,text);	
	return 1;
}
