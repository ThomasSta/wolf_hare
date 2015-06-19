CPP     = g++
CFLAGS  = -O3 -march=native
RM      = rm -f

.PHONY: all clean

all: asdf

clean: 
	$(RM) asdf

vector_skel: asdf.cpp 
	$(CPP) $(CFLAGS) -o $@ $^
