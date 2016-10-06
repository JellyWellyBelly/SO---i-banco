CFLAGS = -g -Wall -pedantic

i-banco: contas.c contas.h i-banco.c commandlinereader.c commandlinereader.h funcoesaux.c funcoesaux.h
	gcc -o i-banco $(CFLAGS) contas.c commandlinereader.c funcoesaux.c i-banco.c
