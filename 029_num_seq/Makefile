CFLAGS=-std=gnu99 -Wall -Werror -pedantic
step1:step1.o
	gcc -o step1 $(CFLAGS) step1.c
step1.o:step1.c
	gcc $(CFLAGS) -c step1.c
step2:step2.o
	gcc -o step2 $(CFLAGS) step2.c
step2.o:step2.c
	gcc $(CFLAGS) -c step2.c
step3:step3.o
	gcc -o step3 $(CFLAGS) step3.c
step3.o:step3.c
	gcc $(CFLAGS) -c step3.c
.PHONY:clean
clean:
	rm -f *~

