CC      = /usr/bin/g++
CFLAGS  = -std=c++11
LDFLAGS = #-lm
SRCDIR = ./src/
OBJDIR = ./objects

OBJ = $(addprefix $(OBJDIR)/, Array.o Game.o main.o )

make: $(OBJ)
	$(CC) $(CFLAGS) -o wolfandhare $(OBJ) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)%.cc
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJDIR)/*.o wolfandhare
