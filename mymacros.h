#ifndef MYMACROS_H
#define MYMACROS_H


		/* * * * * * * * * * * * * * *\
		 *         BIBLIOTECAS       *
		\* * * * * * * * * * * * * * */


#include "commandlinereader.h"
#include "contas.h"
#include "funcoesaux.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>


		/* * * * * * * * * * * * * * *\
		 *           MACROS          *
		\* * * * * * * * * * * * * * */


	/* Comandos Suportados */
#define COMANDO_DEBITAR "debitar"
#define COMANDO_CREDITAR "creditar"
#define COMANDO_LER_SALDO "lerSaldo"
#define COMANDO_SIMULAR "simular"
#define COMANDO_SAIR "sair"
#define COMANDO_SAIR_AGORA "agora"
#define COMANDO_TRANSFERIR "transferir"

	/* Numero maximo de processos */
#define MAXPROSS 20

	/* Constantes das Tarefas */
#define NUM_TRABALHADORAS 3
#define BUFFERSIZE_T (2*NUM_TRABALHADORAS)
#define OP_LERSALDO 0
#define OP_CREDITAR 1
#define OP_DEBITAR 2
#define OP_SAIR 3
#define OP_TRANSFERIR 4
#define ATRIBUTO_NULL -1

	/* Constantes do "Contas" */
#define NUM_CONTAS 10
#define TAXAJURO 0.1
#define CUSTOMANUTENCAO 1

	/* Constantes Gerais */
#define MAXARGS 4
#define BUFFER_SIZE 100
#define ZERO "0"
#define TRUE 1
#define FALSE 0
#define ATIVO 1
#define INATIVO 0
#define ATRASO 1
#define atrasar() sleep(ATRASO)


		/* * * * * * * * * * * * * * *\
		 *     VARIAVEIS GLOBAIS     *
		\* * * * * * * * * * * * * * */


pthread_t tid[NUM_TRABALHADORAS];

#endif




