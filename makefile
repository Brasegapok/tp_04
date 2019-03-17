
directory: directory.c, directory.h, hash.c,hash.h,readfile.c,readile.h
	gcc -std=c11 -Wall -Wextra -fsanitize=address  Serie_1.c -o Serie_1

hash: hash.c, hash.h
	gcc -std=c11 -Wall -Wextra -fsanitize=address  Serie_2.c -o Serie_2
	
readfile: readfile.c,readile.h
	gcc -std=c11 -Wall -Wextra -fsanitize=address  readile.c -o readile
	
	
clear: directory.c, directory.h, hash.c,hash.h,readfile.c,readile.h
	rm -rf directory.c -rf directory.h -rf hash.c  -rf hash.c -rm readfile.c -rm readfile.h