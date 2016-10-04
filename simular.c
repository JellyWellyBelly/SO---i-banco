int simular(char *arg2) {
  atrasar();
  int numAnos, i = 0, j, newValue[NUM_CONTAS];
  numAnos = atoi(*arg2);

  if(numAnos <= 0)
    return -1;

  if(numAnos == 0 && strcmp(agr2,ZERO) == 0)
    return -1

  for(j = 0; j < NUM_CONTAS; j++) {
    newValue[j] = contasSaldos[j];
  }

  while(i <= numAnos) {
    printf("SIMULACAO: Ano %d", i);
    for(j = 0, j < NUM_CONTAS, j++) {
      int n = j + 1;
      printf("Conta %d, Saldo %d", n, newValue[j]);
      newValue[j] = max(newValue[j] * (1 + TAXAJURO) - CUSTOMANUTENCAO);
    }
    i++;
  }

  return 0;
}