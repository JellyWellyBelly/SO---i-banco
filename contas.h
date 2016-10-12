/*
// Operações sobre contas, versao 1
// Sistemas Operativos, DEI/IST/ULisboa 2016-17
*/

#ifndef CONTAS_H
#define CONTAS_H

#define NUM_CONTAS 10
#define TAXAJURO 0.1
#define CUSTOMANUTENCAO 1

#define ATRASO 1

#define ZERO "0"

void inicializarContas();
int contaExiste(int idConta);
int debitar(int idConta, int valor);
int creditar(int idConta, int valor);
int lerSaldo(int idConta);


/* * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Recebe: String que representa um inteiro.       *
 * Retorna: Nada.                                  *
 * Descricao: Simula a evolucao da conta ao fim de *
 *   'n' anos. A simulacao nao é alterada por      *
 *   outras funcoes do codigo-pai.                 *
\* * * * * * * * * * * * * * * * * * * * * * * * * */
void simular(char* arg2);



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 * Recebe: Nada.                                             *
 * Retorna: Nada.                                            *
 * Descricao: Funcao que permite terminar o processo filho.  *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void apanha_sinal();

#endif
