#
# Makefile for the UM 
# edited by Hazen Breen (hbreen01) and Jordan Stone (jstone08)
# 
CC = gcc

IFLAGS  = -I/comp/40/include -I/usr/sup/cii40/include/cii
CFLAGS  = -g -std=gnu99 -Wall -Wextra -Werror -pedantic $(IFLAGS)
LDFLAGS = -g -L/comp/40/lib64 -L/usr/sup/cii40/lib64
LDLIBS  = -l40locality -lbitpack -lcii40 -lm 

EXECS   = interfaces tests writetests 

all: $(EXECS)

um: CPU.o ALU.o sim_mem.o 
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

tests: test_segment.o sim_mem.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

writetests: umlabwrite.o umlab.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECS)  *.o

