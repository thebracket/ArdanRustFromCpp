CC      = gcc
CFLAGS  = -g
RM      = rm -f

default: all

all: unicode

unicode: unicode.c
	$(CC) $(CFLAGS) -o unicode unicode.c

clean veryclean:
	$(RM) unicode
