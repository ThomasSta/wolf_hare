CC      = /usr/bin/g++
CFLAGS  = -std=c++11
LDFLAGS = #-lm
SRCDIR = ./src/
OBJDIR = ./objects

make: main.o
	$(CC) $(CFLAGS) -o wolfandhare main.o $(LDFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJDIR)/*.o wolfandhare
