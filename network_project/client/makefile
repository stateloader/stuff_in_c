src = $(wildcard *.c src/client.c src/scan.c src/connection.c)
obj = $(src:.c=.o)

LDFLAGS = -Wall -lm

prog: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) prog
