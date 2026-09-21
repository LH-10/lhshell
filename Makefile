CC = gcc
LDLIBS = -lreadline
SRC = colors.c shell.c
OBJS= colors.o shell.o
BUILD = build/lhshell


$(BUILD): $(OBJS)
	$(CC)  $^ $(LDLIBS) -o $(BUILD)		

dev: $(BUILD)
	$^

$(OBJS): %.o: %.c 
	$(CC) -c $< -o $@  

$(SRC):
	echo $@" does not exist"

clean_ob: $(OBJS)
	rm $^

