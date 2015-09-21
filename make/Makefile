#Makefile

TARGETS = \
	1\

CPP98 = cpp98
CPP11 = cpp11
$(CPP11):$(TARGETS)
$(CPP98):$(TARGETS)
.PHONY:all
all: $(CPP98)

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
	rm -rf $(TARGETS) *.d core
