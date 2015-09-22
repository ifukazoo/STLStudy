#Makefile

PROG98 = \
	1\

PROG11 = \
	2\

PROG_SORT_TEST = \
	3\

CPP98 = cpp98
CPP11 = cpp11

all: $(PROG98) $(PROG_SORT_TEST)
$(CPP98):$(PROG98)
$(CPP11):$(PROG98) $(PROG11)
sort: $(PROG_SORT_TEST)

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
