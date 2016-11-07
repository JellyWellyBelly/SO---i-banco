/*
 * 
 *               I-BANCO
 * 
 *  Projeto SO - Exercicio 2, version 1
 *  Sistemas Operativos, DEI/IST/ULisboa 2016-17
 *  
 *  Co-autores: Tomas Carrasco nº 84774
 *              Miguel Viegas nº 84747
 *
 */

#include "mymacros.h"

int main (int argc, char** argv) {

    char *args[MAXARGS + 1];
    char buffer[BUFFER_SIZE];

    int pid_list[MAXPROSS], status;

    inicializarContas();
    init_vec_0(pid_list,MAXPROSS);

    cria_pool();
    init_sem();
    init_trincos(NUM_CONTAS);

    printf("Bem-vinda/o ao i-banco\n\n");
      
    while (1) {
        int numargs;
    
        numargs = readLineArguments(args, MAXARGS+1, buffer, BUFFER_SIZE);

        /* EOF (end of file) do stdin ou comando "sair" */
        if (numargs < 0 || (numargs > 0 && (strcmp(args[0], COMANDO_SAIR) == 0))) {
            if (numargs <= 2) {    /* Comando Sair */
                int i, pid_wait, tid_join;

                for(i = 0; i < NUM_TRABALHADORAS; i++) /* Envio da operacao sair */
                    produz(OP_SAIR, ATRIBUTO_NULL, ATRIBUTO_NULL, ATRIBUTO_NULL);

                for(i = 0; i < NUM_TRABALHADORAS; i++) { /* Terminio das tarefas trabalhadoras */
                    tid_join = pthread_join(tid[i], NULL);
                    if(tid_join == 0)
                        printf("TAREFA TERMINADA COM SUCESSO (TID=%ld)\n", tid[i]);
                    else
                        printf("ERRO: TAREFA TERMINADA ABRUPTAMENTE\n");

                }

                printf("i-banco vai terminar.\n--\n");
                for(i = 0; i < MAXPROSS; i++)
                    if(pid_list[i] != 0) {
                        if(numargs > 1 && strcmp(args[1], COMANDO_SAIR_AGORA) == 0) { /* excepcao do sair agora */
                            kill(pid_list[i], SIGUSR1);
                        }
                        pid_wait = waitpid(pid_list[i], &status, 0);
                        printf("FILHO TERMINADO (PID=%d; terminou %s)\n", pid_wait, (WIFEXITED(status)) ? "normalmente" : "abruptamente");
                    }
                printf("--\ni-banco terminou.\n");
            }

            else {
                printf("%s: Sintaxe inválida, tente de novo.\n\n", COMANDO_SAIR);
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
                printf("%s: Sintaxe inválida, tente de novo.\n\n", COMANDO_DEBITAR);
	           continue;
            }

            idConta = atoi(args[1]);
            valor = atoi(args[2]);

            if (!contaExiste(idConta)) {
                printf("%s(%d): Conta não existe.\n\n", COMANDO_DEBITAR, idConta);
                continue;
            }


            produz(OP_DEBITAR, idConta, ATRIBUTO_NULL, valor);
        }

        /* Creditar */
        else if (strcmp(args[0], COMANDO_CREDITAR) == 0) {
            int idConta, valor;

            if (numargs < 3) {
                printf("%s: Sintaxe inválida, tente de novo.\n\n", COMANDO_CREDITAR);
                continue;
            }

            idConta = atoi(args[1]);
            valor = atoi(args[2]);

            if (!contaExiste(idConta)) {
                printf("%s(%d): Conta não existe.\n\n", COMANDO_CREDITAR, idConta);
                continue;
            }

            produz(OP_CREDITAR, idConta, ATRIBUTO_NULL, valor);
        }

        /* Ler Saldo */
        else if (strcmp(args[0], COMANDO_LER_SALDO) == 0) {
            int idConta;

            if (numargs < 2) {
                printf("%s: Sintaxe inválida, tente de novo.\n\n", COMANDO_LER_SALDO);
                continue;            
            }

            idConta = atoi(args[1]);

            if (!contaExiste(idConta)) {
                printf("%s(%d): Conta não existe.\n\n", COMANDO_LER_SALDO, idConta);
                continue;
            }

            produz(OP_LERSALDO, idConta, ATRIBUTO_NULL, ATRIBUTO_NULL);
        }

        /* Transferir */
        else if(strcmp(args[0], COMANDO_TRANSFERIR) == 0) {
            int idContaOrigem, idContaDestino, valor;

            if(numargs < 4) {
                printf("%s: Sintaxe inválida, tente de novo.\n\n", COMANDO_TRANSFERIR);
                continue;
            }

            idContaOrigem = atoi(args[1]);
            idContaDestino = atoi(args[2]);
            valor = atoi(args[3]);

            if (!contaExiste(idContaOrigem) || !contaExiste(idContaDestino)) {
                printf("%s(%d, %d): Conta não existe.\n\n", COMANDO_DEBITAR, idContaOrigem, idContaDestino);
                continue;
            }

            if(idContaOrigem == idContaDestino) {
                printf("%s(%d, %d): id das contas inválidas.\n\n", COMANDO_TRANSFERIR, idContaOrigem, idContaDestino);
                continue;
            }

            produz(OP_TRANSFERIR, idContaOrigem, idContaDestino, valor);
        }

        /* Simular */
        else if (strcmp(args[0], COMANDO_SIMULAR) == 0) {
            int numAnos, pid;

            if (numargs < 2) {
                printf("%s: Sintaxe inválida, tente de novo.\n\n", COMANDO_SIMULAR);
                continue;
            }

           if(list_full(pid_list, MAXPROSS) == TRUE) {
                printf("Erro. Demasiados processos\n\n");
                continue;
            }

            numAnos = atoi(args[1]);

            if(numAnos < 0 || (numAnos == 0 && strcmp(args[1],ZERO) != 0)) {
                printf("%s(%s): Numero de anos inválido.\n\n", COMANDO_SIMULAR, args[1]);
                continue;
            }

            pid = fork();
            
            if(pid < 0) {
                printf("Erro. Processo não criado\n\n");
                continue;
            }

            push_pid(pid_list, MAXPROSS, pid);

            if(pid == 0)  /* Codigo do processo filho. */
                simular(numAnos);
        }

        else {
            printf("Comando desconhecido. Tente de novo.\n\n");
        }
    }
    return 0;
}