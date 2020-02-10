BANBUZ_T = banbuz.o \
		bang.o buzz.o

LPRIME_T = lprime.o \
		crash.o pop.o whizz.o squawk.o zip.o prod.o cackle.o

ALL_T	 = $(BANBUZ_T) $(LPRIME_T) fibbi.o zoob.o sump.o
main: $(ALL_T)

buzzquery: $(ALL_T)

primes: lprime.o crash.o
