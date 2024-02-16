CC      = gcc
CFLAGS  = -g
RM      = rm -f

default: all

all: mutable

hello: mutable.c
	$(CC) $(CFLAGS) -o mutable mutable.c

clean veryclean:
	$(RM) mutable
