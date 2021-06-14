CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic

ODIR = obj

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

Connect4Engine: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/%.o: %.c directories
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR):
	mkdir -p $@

.PHONY: clean directories

directories: $(ODIR)

clean:
	rm -f $(ODIR)/*.o *~ core
