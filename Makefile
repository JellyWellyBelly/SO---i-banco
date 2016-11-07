CFLAGS = -Wall -pedantic -g -c -pthread -lpthread

i-banco: funcoesaux.o commandlinereader.o contas.o i-banco.o
	gcc -pthread -lpthread -o i-banco funcoesaux.o commandlinereader.o contas.o i-banco.o

funcoesaux.o: funcoesaux.c funcoesaux.h mymacros.h
	gcc $(CFLAGS) funcoesaux.c

commandlinereader.o: commandlinereader.c commandlinereader.h mymacros.h
	gcc $(CFLAGS) commandlinereader.c

contas.o: contas.c contas.h mymacros.h
	gcc $(CFLAGS) contas.c

i-banco.o: funcoesaux.o commandlinereader.o contas.o i-banco.c mymacros.h
	gcc $(CFLAGS) i-banco.c

clean:
	rm -f *.o i-banco
