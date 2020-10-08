CFLAGS = -Wall
GENERATES = prog prog-a prog-so README liboutput_static.a liboutput.so
TRASH = *.o *~ o.* *.test

all:    README prog

prog:   const.o fun.o prog.o

README: prog
	./$< 2> $@

fun.o:  outlib.h

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^ 

liboutput.so: fun.c const.c
	$(CC) -fPIC -c -o fun.o fun.c
	$(CC) -fPIC -c -o const.o const.c
	$(CC) -shared fun.o const.o -o $@

prog-a: liboutput_static.a prog.o
	$(CC) prog.o -L. -loutput_static -o $@

prog-so: liboutput.so prog.o
	$(CC) prog.o -L. -loutput -o $@
	
test: prog prog-a prog-so 
	./prog &> t0_1.test 
	./prog-a &> t0_2_.test 
	sed 's/prog-a/prog/g' t0_2_.test > t0_2.test
	./prog-so &> t0_3_.test 
	sed 's/prog-so/prog/g' t0_3_.test > t0_3.test
	./prog one &> t1_1.test 
	./prog-a one &> t1_2.test 
	./prog-so one &> t1_3.test 
	./prog one two three &> t2_1.test 
	./prog-a one two three &> t2_2.test 
	./prog-so one two three &> t2_3.test
	cmp t0_1.test t0_2.test 
	cmp t0_1.test t0_3.test 
	cmp t1_1.test t1_2.test 
	cmp t1_1.test t1_3.test 
	cmp t2_1.test t2_2.test 
	cmp t2_1.test t2_3.test 
