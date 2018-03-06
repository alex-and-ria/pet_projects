#CC=gcc 
CFLAGS  += -g

program_NAME := snfr_d cli1
program_C_SRCS := snfr_d.c cli1.c
program_C_OBJS := ${program_C_SRCS:.c=.o}
program_CNFS:= /sock_file /outlog /logwlan0.txt /loglo.txt /logeth0.txt
all: snfr_d cli1
snfr_d: snfr_d.o
cli1: cli1.o

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_C_OBJS)

distclean: clean
	@- sudo $(RM) $(program_CNFS)
#snfr_d: snfr_d.o
#cli1: cli1.o

#clean:
#	sudo rm -f snfr snfr.o cli1 cli1.o
#	sudo rm -f /sock_file
#	sudo rm -f /outlog
#	sudo rm -f /logwlan0.txt /loglo.txt /logeth0.txt
