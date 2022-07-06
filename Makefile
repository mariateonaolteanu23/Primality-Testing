CC=gcc
CFLAGS= -Wall -Wextra -pedantic
TARGETS=fermat_test.o randomized_fermat_test.o miller_rabin_test.o det_miller_rabin_test.o make_dir

build: $(TARGETS)

make_dir:
	mkdir -p tmp

run-p1:
	./fermat_test

run-p2:
	./randomized_fermat_test

run-p3:
	./miller_rabin_test

run-p4:
	./det_miller_rabin_test

run-best:
	./randomized_fermat_test


primality_utils.o: primality_utils.c
	$(CC) -c $(CFLAGS) $(DEBUG) $^

criterias.o: criterias.c
	$(CC) -c $(CFLAGS) $(DEBUG) $^

accurate_prime.o: accurate_prime.c
	$(CC) -c $(CFLAGS) $(DEBUG) $^


fermat.o: fermat.c 
	$(CC) -c $(CFLAGS) $(DEBUG) $^ 

fermat_test.o: criterias.c fermat.o accurate_prime.o criterias.o primality_utils.o
	$(CC) $(CFLAGS) $(DEBUG) criterias.o accurate_prime.o fermat.o primality_utils.o test.c -o fermat_test -lm
	

randomized_fermat.o: randomized_fermat.c
	$(CC) -c $(CFLAGS) $(DEBUG) $^

randomized_fermat_test.o: criterias.c randomized_fermat.o accurate_prime.o criterias.o primality_utils.o
	$(CC) $(CFLAGS) $(DEBUG) criterias.o accurate_prime.o randomized_fermat.o test.c primality_utils.o -o randomized_fermat_test -lm


miller_rabin.o: miller_rabin.c 
	$(CC) -c $(CFLAGS) $(DEBUG) -c $^

miller_rabin_test.o: test.c miller_rabin.o accurate_prime.o criterias.o primality_utils.o
	$(CC) $(CFLAGS) $(DEBUG) criterias.o accurate_prime.o miller_rabin.o primality_utils.o test.c -o miller_rabin_test -lm


det_miller_rabin.o: det_miller_rabin.c
	$(CC) -c $(CFLAGS) $(DEBUG) -c $^

det_miller_rabin_test.o: test.c det_miller_rabin.o accurate_prime.o criterias.o primality_utils.o
	$(CC) $(CFLAGS) $(DEBUG) criterias.o accurate_prime.o det_miller_rabin.o primality_utils.o test.c -o det_miller_rabin_test -lm

pack:
	zip -FSr maria_teona.olteanu.zip Makefile README *.c *.h in out

.PHONY: clean

clean:
	rm -f *.o *_test test.in test.out exec_time.out
	rm -r tmp

