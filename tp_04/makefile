directory:hash.o,readfile.o,directory.o
	-o 

directory.o: directory.c, directory.h, hash.c,hash.h,readfile.c,readile.h
	gcc -std=c11 -Wall -Wextra -fsanitize=address  Serie_1.c -o Serie_1

hash.o: hash.c, hash.h
	gcc -std=c11 -Wall -Wextra -fsanitize=address  Serie_2.c -o Serie_2
	
readfile.o: readfile.c readile.h
	gcc -std=c11 -Wall -Wextra -fsanitize=address  readile.c -c
	
	
clean:
	rm -rf *.o 