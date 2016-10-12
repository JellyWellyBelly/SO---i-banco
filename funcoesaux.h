#ifndef FUNCOESAUXILIARES_H
#define FUNCOESAUXILIARES_H

#define TRUE 1
#define FALSE 0

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
#endif
