/*
// Projeto SO - exercicio 1, version 1
// Sistemas Operativos, DEI/IST/ULisboa 2016-17
*/

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

#define COMANDO_DEBITAR "debitar"
#define COMANDO_CREDITAR "creditar"
#define COMANDO_LER_SALDO "lerSaldo"
#define COMANDO_SIMULAR "simular"
#define COMANDO_SAIR "sair"
#define COMANDO_SAIR_AGORA "agora"

#define MAXARGS 3
#define BUFFER_SIZE 100
#define MAXPROSS 20


int main (int argc, char** argv) {

    char *args[MAXARGS + 1];
    char buffer[BUFFER_SIZE];
    int pid_list[MAXPROSS], status;

    inicializarContas();
    init_vec_0(pid_list,MAXPROSS);
    
    printf("Bem-vinda/o ao i-banco\n\n");
      
    while (1) {
        int numargs;
    
        numargs = readLineArguments(args, MAXARGS+1, buffer, BUFFER_SIZE);

        /* EOF (end of file) do stdin ou comando "sair" */
        if (numargs < 0 || (numargs > 0 && (strcmp(args[0], COMANDO_SAIR) == 0))) {
            if (numargs == 1) {    /* sair */
                int i, pid_wait;

                printf("i-banco vai terminar.\n--\n");
                for(i = 0; i < MAXPROSS; i++)
                    if(pid_list[i] != 0) {
                        pid_wait = waitpid(pid_list[i], &status, 0);
                        printf("FILHO TERMINADO (PID=%d; terminou %s)\n", pid_wait, (WEXITSTATUS(status) == EXIT_SUCCESS) ? "normalmente" : "abruptamente");
                    }
                printf("--\ni-banco terminou.\n");
            }

            else if(numargs == 2 && (strcmp(args[1], COMANDO_SAIR_AGORA) == 0)) {    /* sair agora */
                int i, sucesso, pid_wait;

                for(i = 0; i < MAXPROSS; i++)
                    if(pid_list[i] != 0) {
                        sucesso = kill(pid_list[i], SIGUSR1);
                        if(sucesso == -1)
                            printf("Erro: Sinal de terminio nao foi possivel de ser enviado ao processo %d.", pid_list[i]);
                        else {
                            pid_wait = waitpid(pid_list[i], &status, 0);
                            printf("FILHO TERMINADO (PID=%d; terminou %s)\n", pid_wait, (WEXITSTATUS(status) == EXIT_SUCCESS) ? "normalmente" : "abruptamente");
                        }
                    }

            }

            else {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_SAIR);
            }            
            
            exit(EXIT_SUCCESS);
        }
    
        else if (numargs == 0)
            /* Nenhum argumento; ignora e volta a pedir */
            continue;
            
        /* Debitar */
        else if (strcmp(args[0], COMANDO_DEBITAR) == 0) {
            int idConta, valor;
            if (numargs < 3) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_DEBITAR);
	           continue;
            }

            idConta = atoi(args[1]);
            valor = atoi(args[2]);

            if (debitar (idConta, valor) < 0)
	           printf("%s(%d, %d): OK\n\n", COMANDO_DEBITAR, idConta, valor);
            else
               printf("%s(%d, %d): OK\n\n", COMANDO_DEBITAR, idConta, valor);
        }

        /* Creditar */
        else if (strcmp(args[0], COMANDO_CREDITAR) == 0) {
            int idConta, valor;
            if (numargs < 3) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_CREDITAR);
                continue;
            }

            idConta = atoi(args[1]);
            valor = atoi(args[2]);

            if (creditar (idConta, valor) < 0)
                printf("%s(%d, %d): Erro\n\n", COMANDO_CREDITAR, idConta, valor);
            else
                printf("%s(%d, %d): OK\n\n", COMANDO_CREDITAR, idConta, valor);
        }

        /* Ler Saldo */
        else if (strcmp(args[0], COMANDO_LER_SALDO) == 0) {
            int idConta, saldo;

            if (numargs < 2) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_LER_SALDO);
                continue;
            }
            idConta = atoi(args[1]);
            saldo = lerSaldo (idConta);
            if (saldo < 0)
                printf("%s(%d): Erro.\n\n", COMANDO_LER_SALDO, idConta);
            else
                printf("%s(%d): O saldo da conta é %d.\n\n", COMANDO_LER_SALDO, idConta, saldo);
        }

        /* Simular */
        else if (strcmp(args[0], COMANDO_SIMULAR) == 0) {
            int pid;

            if (numargs < 2) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_SIMULAR);
                continue;
            }

           if(list_full(pid_list, MAXPROSS) == TRUE) {
                printf("Erro. Demasiados processos\n\n");
                continue;
            }

            pid = fork();
            
            if(pid < 0) {
                printf("Erro. Processo não criado\n\n");
                continue;
            }

            push_pid(pid_list, MAXPROSS, pid);

            if(pid == 0)                        /* processo filho - simular */
                simular(args[1]);
        }

        else {
          printf("Comando desconhecido. Tente de novo.\n");
        }
    }
}