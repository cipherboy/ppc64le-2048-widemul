CC?=gcc
CFLAGS+=-Wall -Werror -Wextra -std=c99 -pedantic -Isrc -Wno-unused-parameter

build/.objects:
	mkdir -p build/.objects

src: build/.objects build/.objects/rsa2048-impl-uint64t.o

build/.objects/rsa2048-impl-uint64t.o: src/rsa2048-impl-uint64t.c
	${CC} -c ${CFLAGS} -o $@ src/rsa2048-impl-uint64t.c

clean:
	rm -rf build/
