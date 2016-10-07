#include "contas.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define atrasar() sleep(ATRASO)
#define ATIVA 1
#define INATIVA 0

int contasSaldos[NUM_CONTAS];
int flag_terminio = INATIVA;

int contaExiste(int idConta) {
  return (idConta > 0 && idConta <= NUM_CONTAS);
}

void inicializarContas() {
  int i;
  for (i=0; i<NUM_CONTAS; i++)
    contasSaldos[i] = 0;
}

int debitar(int idConta, int valor) {
  atrasar();
  if (!contaExiste(idConta)) /* verifica se conta existe */
    return -1;
  if (contasSaldos[idConta - 1] < valor) /* verifica se tem saldo suficiente */
    return -1;
  atrasar();
  contasSaldos[idConta - 1] -= valor; /* retira dinheiro hehehehe */
  return 0;
}

int creditar(int idConta, int valor) {
  atrasar();
  if (!contaExiste(idConta)) /* verifica se conta existe */
    return -1;
  contasSaldos[idConta - 1] += valor; /* mete plin plin */
  return 0;
}

int lerSaldo(int idConta) {
  atrasar();
  if (!contaExiste(idConta))
    return -1;
  return contasSaldos[idConta - 1];
}

//o signal ativa uma funcao auxiliar. funcao esta que vai efetivamente interromper o processo. 
//o kill é o que envia o sinal(recebido pelo signal) para o processo filho
void apanha_sinal(int pid) { 
     flag_terminio = ATIVA;
}

void simular(char *arg2) {
  signal(SIGUSR1,apanha_sinal);
  int numAnos, i, j;
  int newValue[NUM_CONTAS];
  numAnos = atoi(arg2);

  if(numAnos <= 0)
    exit(1);

  if(numAnos == 0 && strcmp(arg2,ZERO) != 0)
    exit(1);

  for(j = 0; j < NUM_CONTAS; j++) {
    newValue[j] = contasSaldos[j];
  }

  i = 0;
  while(i <= numAnos) {

    if (flag_terminio == ATIVA){
        printf("Simulacao terminada por sinal.\n");
        exit(0);
    }
    atrasar();

    printf("SIMULACAO: Ano %d\n", i);
    printf("=================\n");
    for(j = 0; j < NUM_CONTAS; j++) {
      int n = j + 1;
      
      if(newValue[j] >= 0)
        printf("Conta %d, Saldo %d\n", n, newValue[j]);
      else
        printf("Conta %d, Saldo 0\n", n);
      newValue[j] = (newValue[j] * (1 + TAXAJURO) - CUSTOMANUTENCAO);
    }
    printf("\n");
    i++;
  }

  exit(0);
}