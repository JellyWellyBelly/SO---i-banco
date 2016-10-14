CFLAGS = -Wall -pedantic -g -c

i-banco: funcoesaux.o commandlinereader.o contas.o i-banco.o
	gcc -o i-banco funcoesaux.o commandlinereader.o contas.o i-banco.o

funcoesaux.o: funcoesaux.c funcoesaux.h
	gcc $(CFLAGS) funcoesaux.c

commandlinereader.o: commandlinereader.c commandlinereader.h
	gcc $(CFLAGS) commandlinereader.c

contas.o: contas.c contas.h
	gcc $(CFLAGS) contas.c

i-banco.o: funcoesaux.o commandlinereader.o contas.o i-banco.c
	gcc $(CFLAGS) i-banco.c

clean:
	rm -f *.o i-banco
