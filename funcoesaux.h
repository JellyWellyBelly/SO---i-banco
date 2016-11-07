#ifndef FUNCOESAUXILIARES_H
#define FUNCOESAUXILIARES_H

#include "mymacros.h"


		/* * * * * * * * * * * * * * *\
		 *         ESTRUTURAS        *
		\* * * * * * * * * * * * * * */


typedef struct Operacao {
	int operacao;
	int idConta;
	int idContaDestino;
	int valor;

} comando_t; 



		/* * * * * * * * * * * * * * *\
		 *          FUNCOES          *
		\* * * * * * * * * * * * * * */


		/* * * * * * * * * * * * * * *\
		 * Funcionais sobre vetores  *
		\* * * * * * * * * * * * * * */


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Recebe: Ponteiro para um vetor de inteiros.           *
 *         O tamanho do vetor (inteiros).                *
 * Retorna: Nada.                                        *
 * Descricao: Todas as entradas sao inicializadas a '0'  *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void init_vec_0(int *vec, int size);



/* * * * * * * * * * * * * * * * * * * * * * * *\
 * Recebe: Ponteiro para um vetor de inteiros. *
 *         Tamanho do vetor (inteiro).         *
 *         Um Pid (inteiro)                    *
 * Retorna: Nada.                              *
 * Descricao: Coloca o valor do pid no vetor.  *
 *   '0' nao é valor de nenhum pid.            *
\* * * * * * * * * * * * * * * * * * * * * * * */
void push_pid(int *vec, int size, int pid);



/* * * * * * * * * * * * * * * * * * * * * * * * * *\ 
 * Recebe: Um ponteiro para um vetor de inteiros.  *
 *         O tamanho para um vetor (inteiro).      *
 * Retorna: Inteiro correpondente a valor logico.  *
 * Descricao: Retorna "True" se a lista nao tem    *
 *   entradas a '0', "False" caso contrario.       *
\* * * * * * * * * * * * * * * * * * * * * * * * * */
int list_full(int *vec, int size);



		/* * * * * * * * * * * * * * *\
		 * Inicializacao dos objetos *
		 *     de sincronizacao      *
		\* * * * * * * * * * * * * * */


/* * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Recebe: Numero de contas maximo do banco.         *
 * Retorna: Nada.                                    *
 * Descricao: Inicializa todos os trincos presentes  *
 *				no programa todo.                    *
\* * * * * * * * * * * * * * * * * * * * * * * * * * */
void init_trincos(int n_contas);


/* * * * * * * * * * * * * * * * * * * * * * *\
 * Recebe: Nada.                             *
 * Retorna: Nada.                            *
 * Descricao: Inicializa todos os semaforos  *
 *              presentes no programa todo.  *
\* * * * * * * * * * * * * * * * * * * * * * */
void init_sem();


/* * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Recebe: Nada.                                   *
 * Retorna: Nada.                                  *
 * Descricao: Cria a "pool" de tarefas que realiza *
 				as operacoes sobre as contas.      *
\* * * * * * * * * * * * * * * * * * * * * * * * * */
void cria_pool();


		/* * * * * * * * * * * * * * *\
		 * Produtores e Consumidores *
		\* * * * * * * * * * * * * * */


/* * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Recebe: Id da operacao.                             *
 *         Id da conta original.                       *
 *         Id da conta destino.                        *
 *         Valor do montante a creditar ou debitar.    *
 * Retorna: Nada.                                      *
 * Descricao: Coloca no buffer os comandos a realizar  *
 *              pelas tarefas trabalhadoras. Se cheio  *
 *              "espera" ate' ter espaco livre.        *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * */
void produz(int op, int id, int idFim, int valor);


/* * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Recebe: Nada.                                     *
 * Retorna: Nada.                                    *
 * Descricao: Retira do buffer o comando a realizar. *
 *              Evoca a funcao "trata_comando" que   *
 *              efetivamente realiza a operacao.     *
 *				Se vazio, "espera".                  *
\* * * * * * * * * * * * * * * * * * * * * * * * * * */
void *consome();


/* * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Recebe: Comando (Tipo de dados = Estrutura acima)   *
 * Retorna: Nada.                                      *
 * Descricao: Realiza a operacao.                      *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * */
void trata_comando(comando_t comando);

#endif