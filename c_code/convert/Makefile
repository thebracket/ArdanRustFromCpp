CC      = gcc
CFLAGS  = -g
RM      = rm -f

default: all

all: convert

convert: convert.c
	$(CC) $(CFLAGS) -o convert convert.c

clean veryclean:
	$(RM) convert
