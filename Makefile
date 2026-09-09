CC = gcc
LDLIBS = -lreadline
SRC = colors.c shell.c
OBJS= colors.o shell.o
BUILD = build/lhshell


$(BUILD): $(OBJS)
	$(CC)  $^ $(LDLIBS) -o $(BUILD)		

dev: $(BUILD)
	$^

$(SRC): 
	$(CC) -c $@  
shell.c:
	echo "source does not exist"

