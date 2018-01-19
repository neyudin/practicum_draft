CC = @gcc
CFLAGS = -m32 -O2 -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -std=gnu11
LDLIBS = -lm
LDFLAGS = -m32
all: genrand
genrand: main.o rand.o
	$(CC) $(LDFLAGS) $^ -o $@
main.o: main.c rand.h
	$(CC) $(LDLIBS) $(CFLAGS) -c $< -o $@
rand.o: rand.c
	$(CC) $(LDLIBS) $(CFLAGS) -c $< -o $@
clean:
	@-rm -f *.o genrand