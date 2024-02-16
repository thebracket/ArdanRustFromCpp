CC      = gcc
CFLAGS  = -g
RM      = rm -f

default: all

all: primitives sized_primitives

primitives: primitives.c
	$(CC) $(CFLAGS) -o primitives primitives.c

sized_primitives: sized_primitives.c
	$(CC) $(CFLAGS) -o sized_primitives sized_primitives.c

clean veryclean:
	$(RM) primitives
	$(RM) sized_primitives
