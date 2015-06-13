VERSION = 0.0.1

INCLUDE = -Ipostgres/src/include
#INCLUDE = -Ipsql/include -Ipostgres/src/include

CC = clang
#CFLAGS = -Wall -Wconversion -Wextra -O0 -g -ggdb -march=native -mtune=native -fPIC $(INCLUDE)
#CFLAGS = -Wall -Wconversion -Wextra -O0 -g2 -ggdb -march=native -mtune=native -Wshadow -Wfloat-equal -Wlogical-op -D_FORTIFY_SOURCE=2 -fsanitize=address,leak,undefined -fPIC $(INCLUDE)
#CFLAGS = -Wall -Wconversion -Wextra -Og -g2 -ggdb -march=native -mtune=native -Wshadow -Wfloat-equal -Wlogical-op -fPIC $(INCLUDE)
CFLAGS = -Wall -Wconversion -Wextra -Werror -O3 -march=native -mtune=native -Wshadow -Wfloat-equal -fPIC $(INCLUDE)

all: util.o levenshtein.o jaccard.o playground.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBRARY) util.o levenshtein.o jaccard.o playground.o -Wl,-soname,libplayground.so.$(VERSION) -Wl,-O1 -shared -o libplayground.so.$(VERSION)

gcc: CC = gcc
gcc: all

clean:
	rm -rf *.o libplayground.so.$(VERSION)

install:
	install -m 0755 libplayground.so.0.0.1 psql/lib/postgresql/libplayground.so.0.0.1
	ln -sfr psql/lib/postgresql/libplayground.so.0.0.1 psql/lib/postgresql/libplayground.so.0
	ln -sfr psql/lib/postgresql/libplayground.so.0.0.1 psql/lib/postgresql/libplayground.so
