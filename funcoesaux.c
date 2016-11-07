#include "funcoesaux.h"

comando_t buffer_com[BUFFERSIZE_T];
int prodptr = 0;
int consptr = 0;

sem_t semaforo_p;
sem_t semaforo_c;

pthread_mutex_t trinco_p, trinco_c;
pthread_mutex_t vec_trinco[NUM_CONTAS];


void init_vec_0(int *vec, int size) {
	int i = 0;

	while (i < size) {
		vec[i] = 0;
		i++;
	}
}

void push_pid(int *vec, int size, int pid) {
	int i = 0;

	while (i < size) {
		if (vec[i] == 0) {
			vec[i] = pid;
			return;
		}
		i++;
	}
}

int list_full(int *vec, int size) {
	int i = 0;

	while (i < size) {
		if (vec[i] == 0)
			return FALSE;
		i++;
	}
	return TRUE;
}

void init_trincos(int n_contas) {
	int i;

	for(i = 0; i < n_contas; i++)
		if(pthread_mutex_init(&vec_trinco[i], 0))
			exit(1);

	if(pthread_mutex_init(&trinco_p, 0))
        exit(1);
    
    if(pthread_mutex_init(&trinco_c, 0))
        exit(1);
}

void init_sem() {
    if(sem_init(&semaforo_p, 0, BUFFERSIZE_T))
        exit(1);
    if(sem_init(&semaforo_c, 0, 0))
        exit(1);
}

void cria_pool() {
	int i, err;

	for (i = 0; i < NUM_TRABALHADORAS; i++) {
		 err = pthread_create(&tid[i], NULL, consome, NULL);
		 if(err != 0) {
		 	printf("ERRO NA CRIACAO DA POOL\n\n");
		 	exit(1);
		 }
	}
}

void produz(int op, int id, int idFim, int valor) {
	comando_t comando;

	sem_wait(&semaforo_p);
	pthread_mutex_lock(&trinco_p);

	comando.operacao = op;
	comando.idConta = id;
	comando.idContaDestino = idFim;
	comando.valor = valor;

	buffer_com[prodptr] = comando;
	prodptr = (prodptr + 1) % BUFFERSIZE_T;

	pthread_mutex_unlock(&trinco_p);
	sem_post(&semaforo_c);
} 

void *consome() {
	comando_t comando;

	sleep(5);

	while(TRUE) {
		sem_wait(&semaforo_c);
		pthread_mutex_lock(&trinco_c);

		comando = buffer_com[consptr];
		consptr = (consptr + 1) % BUFFERSIZE_T;

		pthread_mutex_unlock(&trinco_c);
		sem_post(&semaforo_p);

		trata_comando(comando);

	}

	return NULL;
}

void trata_comando(comando_t comando) {
	int idConta = comando.idConta,
		idContaDestino = comando.idContaDestino,
		valor = comando.valor,
		saldo;

	switch(comando.operacao) {

		case OP_DEBITAR: {
			
			pthread_mutex_lock(&vec_trinco[idConta]);

			if (debitar(idConta, valor) < 0)
	          	printf("%s(%d, %d): Erro\n\n", COMANDO_DEBITAR, idConta, valor);
          	else
              	printf("%s(%d, %d): OK\n\n", COMANDO_DEBITAR, idConta, valor);

			pthread_mutex_unlock(&vec_trinco[idConta]);

          	break;
          }

		case OP_CREDITAR: {

			pthread_mutex_lock(&vec_trinco[idConta]);

			if (creditar(idConta, valor) < 0)
                printf("%s(%d, %d): Erro\n\n", COMANDO_CREDITAR, idConta, valor);
            else
                printf("%s(%d, %d): OK\n\n", COMANDO_CREDITAR, idConta, valor);

            pthread_mutex_unlock(&vec_trinco[idConta]);

            break;
        }

        case OP_LERSALDO: {

        	pthread_mutex_lock(&vec_trinco[idConta]);

        	saldo = lerSaldo(idConta);

        	if (saldo < 0)
                printf("%s(%d): Erro.\n\n", COMANDO_LER_SALDO, idConta);
            else
                printf("%s(%d): O saldo da conta é %d.\n\n", COMANDO_LER_SALDO, idConta, saldo);

            pthread_mutex_unlock(&vec_trinco[idConta]);

            break;
		}

		case OP_TRANSFERIR: {

			if(transferir(idConta, idContaDestino, valor) < 0)
				printf("Erro ao %s %d da conta %d para a conta %d.\n\n", COMANDO_TRANSFERIR, valor, idConta, idContaDestino);
			else
				printf("%s(%d, %d, %d): OK\n\n", COMANDO_TRANSFERIR, idConta, idContaDestino, valor);

		}

        case OP_SAIR: {

        	pthread_exit(NULL);
        }
	 }
}