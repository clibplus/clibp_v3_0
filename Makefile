.PHONY: all

all: compile

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
	gcc t.c -o t build/lib.o
