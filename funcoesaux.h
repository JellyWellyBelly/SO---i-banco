#ifndef FUNCOESAUXILIARES_H
#define FUNCOESAUXILIARES_H

#define TRUE 1
#define FALSE 0

/* Inicializa um vetor com 0's */
void init_vec_0(int *vec, int size);

/* Coloca o id na lista*/
void push_pid(int *vec, int size, int pid);

/* Verifica se a lista de pids está cheia*/
int list_full(int *vec, int size);
#endif