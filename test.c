#include <stdio.h>
#include "colors.h"

int main(){
	char mystr[300];
	make_colored_text(mystr,sizeof(mystr),C_RED,"mytext");
	printf("text: %s",mystr);	
}
