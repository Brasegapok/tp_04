directory: hash.o readfile.o directory.o
    gcc -o hash.o readfile.o directory.o directory

directory.o: directory.c directory.h hash.c hash.h readfile.c readile.h
    gcc -std=c11 -Wall -Wextra -fsanitize=address  directory.c -c

hash.o: hash.c hash.h
    gcc -std=c11 -Wall -Wextra -fsanitize=address  hash.c -c
    
readfile.o: readfile.c readile.h
    gcc -std=c11 -Wall -Wextra -fsanitize=address  readile.c -c

clean:
    rm -rf *.o

