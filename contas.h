/*
// Operações sobre contas, versao 2
// Sistemas Operativos, DEI/IST/ULisboa 2016-17
*/

#ifndef CONTAS_H
#define CONTAS_H

#include "mymacros.h"

void inicializarContas();
int contaExiste(int idConta);
int debitar(int idConta, int valor);
int creditar(int idConta, int valor);
int lerSaldo(int idConta);


/*            *\
 * COMENTAR!! *
\*            */
int transferir(int idContaOrigem, int idContaDestino, int valor);

/* * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Recebe: Um inteiro.                             *
 * Retorna: Nada.                                  *
 * Descricao: Simula a evolucao da conta ao fim de *
 *   'n' anos. A simulacao nao é alterada por      *
 *   outras funcoes do codigo-pai.                 *
\* * * * * * * * * * * * * * * * * * * * * * * * * */
void simular(int numAnos);



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Recebe: Nada.                                             *
 * Retorna: Nada.                                            *
 * Descricao: Funcao que permite terminar o processo filho.  *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void apanha_sinal();

#endif
