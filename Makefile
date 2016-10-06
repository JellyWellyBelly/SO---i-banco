CFLAGS = -g -Wall -pedantic

i-banco: contas.c contas.h i-banco.c commandlinereader.c commandlinereader.h funcoesauxiliares.c funcoesauxiliares.h
	gcc -o i-banco $(CFLAGS) contas.c commandlinereader.c funcoesauxiliares.c i-banco.c
