CC = gcc
LDLIBS = -lreadline

build/lhshell: shell.o
	$(CC)  shell.o $(LDLIBS) -o build/lhshell		

dev: build/lhshell
	./build/lhshell

shell.o: shell.c
	$(CC) -c  shell.c -o shell.o 
shell.c:
	echo "source does not exist"

