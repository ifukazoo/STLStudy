#Makefile

PROG98 = \
	1\

PROG11 = \
	2\

CPP98 = cpp98
CPP11 = cpp11

all: $(PROG98)
$(CPP98):$(PROG98)
$(CPP11):$(PROG98) $(PROG11)

CC   =  g++
CFLAGS = -Wall -MD
VPATH = ../src

ifeq ($(MAKECMDGOALS), $(CPP11))
CFLAGS += -std=c++11
endif

%:%.cc
	$(CC) $(CFLAGS) $< -o $*

-include *.d

.PHONY:clean
clean:
	rm -rf $(PROG98) $(PROG11) *.d core tags
