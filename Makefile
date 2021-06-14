CFLAGS = -Wall -Wextra

BIN = Connect4Engine

SRCDIR = src
ODIR = obj

_OBJ = main.o board.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Make binary
$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# object files go in the /obj folder
$(ODIR)/%.o: $(SRCDIR)/%.c $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

# create object folder /opt if it doesn't exist
$(ODIR):
	mkdir -p $@

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(BIN)
