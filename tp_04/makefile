directory: hash.o readfile.o directory.o
	gcc -o hash.o readfile.o directory.o

directory.o: directory.c hash.c hash.h readfile.c readfile.h
	gcc -std=c11 -Wall -Wextra -fsanitize=address  directory.c -c

hash.o: hash.c hash.h
	gcc -std=c11 -Wall -Wextra -fsanitize=address  hash.c -c

hash_test.o: hash_test.c hash.c hash.h
	gcc -std=c11 -Wall -Wextra -fsanitize=address  hash_test.c -c
readfile.o: readfile.c readfile.h
	gcc -std=c11 -Wall -Wextra -fsanitize=address  readfile.c -c

clean:
	rm -rf *.o

