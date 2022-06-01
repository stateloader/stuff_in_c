src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -Wall -lm

client: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) client
