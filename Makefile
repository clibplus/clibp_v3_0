.PHONY: all

all: compile

clean:
	rm -rf build

dir:
	mkdir -p build

move:
	cp -r headers/* /usr/local/include

test:
	gcc t.c -o build/app \
	src/*.c \
	src/stdlib/*.c build/lib.o \
	-ggdb

count:
	wc -l t.c \
	src/*.c \
	src/stdlib/*.c \
	headers/*.h \
	headers/stdlib/*.h

compile:
	nasm -f elf64 asm/x86_64/lib.asm -o build/lib.o

	rm -rf *.o
	gcc -c src/*.c \
	src/stdlib/*.c \
	src/libs/*.c \
	-nostdlib
	ar rcs build/libclibp.a *.o
	ar rcs build/clibp.o *.o
	rm -rf *.o

	gcc t.c -o t \
	src/*.c \
	src/stdlib/*.c \
	src/libs/*.c \
	build/lib.o \
	-ggdb

cloader:
	gcc -c linker/gcc_clibp.c -o gcc_clibp.o -nostdlib
	gcc -c loader/loader.c -o loader/loader.o -nostdlib -ffunction-sections -Wl,--gc-sections
	ld -o gcc_clibp gcc_clibp.o build/lib.o
	rm gcc_clibp.o
