main.o: main.c declarations.h
	gcc -c main.c

csv2sql: main.o
	gcc main.o -o csv2sql

clean:
	rm main.o csv2sql.exe
