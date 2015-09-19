#Makefile

TARGETS = \
						1\

all:$(TARGETS)

CC   =  g++
CFLAGS = -Wall -MD
VPATH = ../src

%:%.cc
	$(CC) $(CFLAGS) $< -o $*

-include *.d

.PHONY:	clean
clean:
	rm -rf $(TARGETS) *.d core
