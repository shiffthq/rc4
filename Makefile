CC := gcc

CFLAGS := -g -Wall -O3 -DLINUX -Isrc

SOFLAGS := -g -DLINUX -shared -fPIC -Isrc

LDFLAGS := -Wl,-rpath,bin,-rpath,-Lbin,-lstdc++

# vpath indicate the searching path of the according file type
vpath %.c src
vpath %.h src
vpath %.c example
vpath %.c test
vpath %.h test
vpath %.so bin
vpath % bin

rc4_test: main_test.c rc4.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@
	./$@
	rm ./$@

rc4_example: example.c rc4.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@
	./$@
	rm ./$@

lib%.a: %.c
	ar rcs $@ $^

lib%.so: %.c
	$(CC) $^ $(SOFLAGS) -o $@

.PHONY : clean
clean :
	rm -rf *.dSYM

