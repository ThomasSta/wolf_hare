CPP     = mpic++ #g++
CFLAGS  = -O3 -march=native
RM      = rm -f

.PHONY: all clean

all: asdf

clean: 
	$(RM) asdf

asdf: asdf.cpp 
	$(CPP) $(CFLAGS) -o $@ $^
