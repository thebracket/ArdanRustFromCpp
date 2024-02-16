CC      = gcc
CFLAGS  = -g
RM      = rm -f

default: all

all: overflow overflow_safe

overflow: overflow.c
	$(CC) $(CFLAGS) -o overflow overflow.c

overflow_safe: overflow_safe.c
	$(CC) $(CFLAGS) -o overflow_safe overflow_safe.c

clean veryclean:
	$(RM) overflow
