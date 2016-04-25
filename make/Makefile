#Makefile

CPP98     := 1
CPP11     := 2
SORT      := 3
EFFECTIVE := 4
THREAD    := 5
PROGRAMS  := $(CPP98) $(CPP11) $(SORT) $(EFFECTIVE) $(THREAD)

all:       $(PROGRAMS)
cpp98:     $(CPP98)
cpp11:     $(CPP11)
sort:      $(SORT)
effective: $(EFFECTIVE)
thread:    $(THREAD)

vpath %.cc ../src
vpath %.h  ../include

CPPFLAGS = -I ../include -Wall -Wextra -MMD -MP
$(CPP11):     CPPFLAGS += -std=c++11
$(EFFECTIVE): CPPFLAGS += -std=c++11
$(THREAD):    CPPFLAGS += -std=c++11 -pthread

-include *.d
.PHONY:clean
clean:
	rm -rf $(PROGRAMS) *.d *.o core tags
