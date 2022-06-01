src = $(wildcard *.c src/client.c src/scan/scan.c src/session/session.c)
obj = $(src:.c=.o)

LDFLAGS = -Wall -lm

client: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) client
