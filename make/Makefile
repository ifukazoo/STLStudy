#Makefile

CPP98 := 1
CPP11 := 2
SORT  := 3
BINARY := $(CPP98) $(CPP11) $(SORT)

all: $(CPP98) $(CPP11) $(SORT)
cpp98: $(CPP98)
cpp11: $(CPP11)
sort:  $(SORT)

vpath %.cc ../src
vpath %.h  ../include

CPPFLAGS = -I ../include -Wall -Wextra -MMD -MP
$(CPP11) : CPPFLAGS += -std=c++11

-include *.d
.PHONY:clean
clean:
	rm -rf $(BINARY) *.d *.o core tags
