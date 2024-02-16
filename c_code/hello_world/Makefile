CC      = gcc
CFLAGS  = -g
RM      = rm -f

default: all

all: hello

hello: hello_world.c
	$(CC) $(CFLAGS) -o hello hello_world.c

clean veryclean:
	$(RM) hello
