run_maxSeq: test-subseq.o maxSeq.o
	gcc -o run_maxSeq maxSeq.o test-subseq.o -Wall -Wextra --pedantic --std=gnu99

maxSeq.o: maxSeq.c
	gcc -Wall -Wextra --pedantic --std=gnu99 -c maxSeq.c

test-subseq.o: test-subseq.c
	gcc -Wall -Wextra --pedantic --std=gnu99 -c test-subseq.c

.PHONY: clean

clean:
	rm -f *.o *~ run_maxSeq
