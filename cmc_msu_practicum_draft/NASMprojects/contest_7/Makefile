all: main__3 main__1 sortf.o
	gcc -m32 -o sort_ascend main_ascend.o sortf.o
	gcc -m32 -o sort_descend main_descend.o sortf.o
	rm -f main_ascend.o main_descend.o sortf.o
main__3: main.c sortdecl.h
	gcc -m32 -DCOMPARE_CG -std=c99 -O2 -c main.c -o main_ascend.o
main__1: main.c sortdecl.h
	gcc -m32 -std=c99 -O2 -c main.c -o main_descend.o
sortf.o: sortf.asm
	nasm -f elf32 -o sortf.o sortf.asm
ascend:	main_3 sortf.o
	gcc -m32 -o sort main.o sortf.o
descend: main_1 sortf.o
	gcc -m32 -o sort main.o sortf.o
main_3: main.c sortdecl.h
	gcc -m32 -DCOMPARE_CG -std=c99 -O2 -c main.c -o main.o
main_1: main.c sortdecl.h
	gcc -m32 -std=c99 -O2 -c main.c -o main.o
debug: main___3 main___1 sortf.o
	gcc -m32 -o sort_ascend_debug main_ascend_debug.o sortf.o
	gcc -m32 -o sort_descend_debug main_descend_debug.o sortf.o
	rm -f main_ascend_debug.o main_descend_debug.o sortf.o
main___3: main_debug.c sortdecl.h
	gcc -m32 -DCOMPARE_CG -std=c99 -O2 -c main_debug.c -o main_ascend_debug.o
main___1: main_debug.c sortdecl.h
	gcc -m32 -std=c99 -O2 -c main_debug.c -o main_descend_debug.o
clean:
	rm -f sort_ascend sort_descend main.o sortf.o sort sort_ascend_debug sort_descend_debug