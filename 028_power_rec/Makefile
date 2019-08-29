CFLAGS=-ggdb3 -Wall -Werror -std=gnu99 -pedantic

test: test-power.o power.o
	gcc $(CFLAGS) -o $@ $^

test-power.o:test-power.c
	gcc $(CFLAGS) -c test-power.c

power.o:power.c
	gcc $(CFLAGS) -c power.c

.PHONY:clean
clean:
	rm -f power test-power *~
