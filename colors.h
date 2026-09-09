#include <stddef.h>
#ifndef TCOLORS_H
#define TCOLORS_H

extern const char C_RED[];
extern const char C_BLUE[];
extern const char C_YELLOW[];
extern const char C_GREEN[];
extern const char C_CYAN[];
extern const char C_MAGENTA[];
extern const char C_RESET[];

int  make_colored_text(char buf[],size_t bufsize,const char color[],const char text[]);

#endif
