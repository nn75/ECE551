CFLAGS=-ggdb3 -Wall -std=gnu99 -pedantic
test:test-subseq.o maxSeq.o
	gcc $(CFLAGS) -o $@ $^
test-subseq.o:test-subseq.c
	gcc $(CFLAGS) -c test-subseq.c
maxSeq.o:maxSeq.c
	gcc $(CFLAGS) -c maxSeq.c
.PHONY:clean
clean:
	rm -f test test-subseq *~

