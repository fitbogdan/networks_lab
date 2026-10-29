# Builds every .c file in this folder into a binary with the same name
# (ex1_serv.c -> ex1_serv). Change INC if netio.h moves
CC      = gcc
CFLAGS  = -Wall -Wextra -g
INC     = ../common

SRCS = $(wildcard *.c)
BINS = $(SRCS:.c=)

all: $(BINS)

%: %.c $(INC)/netio.h
	$(CC) $(CFLAGS) -I $(INC) $< -o $@

clean:
	rm -f $(BINS)

.PHONY: all clean
