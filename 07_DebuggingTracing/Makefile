CC = gcc
CFLAGS = -shared -fPIC
SOURCE = fake.c
LIBNAME = libfake.so
TEST1 = dummy
TEST2 = dummyFIXME
TESTFILES = $(TEST1) $(TEST2)
GENERATES = $(LIBNAME) $(TESTFILES)

makelib:
	$(CC) $(CFLAGS) $(SOURCE) -ldl -o $(LIBNAME)

clean:
	rm -f $(GENERATES)

test:	clean
	touch $(TESTFILES)
	rm -f $(TESTFILES)
	[ ! -f $(TEST1) ]
	[ ! -f $(TEST2) ]
	make makelib
	touch $(TESTFILES)
	LD_PRELOAD=./$(LIBNAME) rm -f $(TESTFILES)
	[ ! -f $(TEST1) ]
	[ ! -f $(TEST2) ]
	make clean

