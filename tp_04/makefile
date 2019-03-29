directory: hash.o readfile.o directory.o
	gcc -o hash.o readfile.o directory.o directory

directory.o: directory.c hash.c hash.h readfile.c readfile.h
	gcc -std=c11 -Wall -Wextra -fsanitize=address  directory.c -c

hash.o: hash.c hash.h
	gcc -std=c11 -Wall -Wextra -fsanitize=address  hash.c -c
    
readfile.o: readfile.c readfile.h
	gcc -std=c11 -Wall -Wextra -fsanitize=address  readfile.c -c

clean:
	rm -rf *.o

